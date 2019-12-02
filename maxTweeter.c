// Authors: Shruthi Sankarram (913642322) && Amy Woods (913770977)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*
	TweeterInformation struct carries information of an individual tweeter, holding its username and the numberOfTweets the Tweeter has tweeted. 
*/
struct TweeterInformation {
	int numberOfTweets;
	char* tweeter_username;
};

/*
	Boolean to indicate whether an exit(0) should occur.
*/
bool mustExitProgram;


/*
	Quicksort helper algorithm.
*/
int partition(struct TweeterInformation *tweeterFrequency, int ** top10Arr, int lowIndex, int highIndex){
	int pivotIndex = (*top10Arr)[highIndex];
	int pivot = tweeterFrequency[pivotIndex].numberOfTweets;

	int i = lowIndex - 1;

	for(int j = lowIndex; j <= highIndex -	1; j++){
		int realIndex = (*top10Arr)[j];
		if(tweeterFrequency[realIndex].numberOfTweets < pivot){
			i++;
			int temp = (*top10Arr)[i];
			(*top10Arr)[i] = (*top10Arr)[j];
			(*top10Arr)[j] = temp;
		} // end if 
	} // end for

	int temp = (*top10Arr)[i+1];
	(*top10Arr)[i+1] = (*top10Arr)[highIndex];
	(*top10Arr)[highIndex] = temp;
	return (i+1);
} // end partition function

/*
	Quicksort algorithm.
*/
void top10(struct TweeterInformation *tweeterFrequency, int ** top10Arr, int lowIndex, int highIndex){
	if(lowIndex < highIndex){
		int partitionIndex = partition(tweeterFrequency, top10Arr, lowIndex, highIndex);
		top10(tweeterFrequency, top10Arr, lowIndex, partitionIndex -1);
		top10(tweeterFrequency, top10Arr, partitionIndex + 1, highIndex);
	} // end if
} // end top10 function


/*
	For header row - determines if there are wrapping quotes around a string, and if the quotes match correctly.
*/
bool checkMatchingEndQuotes(char* tempString){
	bool matchingQuotesEnd = true; 

	if(strlen(tempString) == 1 && tempString[0] == '\"') {
		// string length is one, and it is just a quote.
		matchingQuotesEnd = false;
	} else if(tempString[0] == '\"' && tempString[strlen(tempString) - 1] != '\"' ){ 
		// only beginning character is a quote
		matchingQuotesEnd = false;
	} else if(tempString[0] != '\"' && tempString[strlen(tempString) - 1] == '\"'){ 
		// only end character is a quote
		matchingQuotesEnd = false;
	} // end else if

	return matchingQuotesEnd;
} // end checkMatchingEndQuotes function


/*
	For body rows - determines if there are wrapping quotes around a string, and if the quotes match correctly.
*/
bool checkHeaderContentEndQuoteMatching(char* content, bool* headerSurroundedByQuotes, int index, int numberOfColumns, bool isAtLastRow){
	bool matchingQuotesEnd = true;

	if(content[strlen(content) - 1] == '\n' && content[strlen(content) - 2] != '\r'){
		if (isAtLastRow == true){
			if(strlen(content) == 2 && content[0] == '\"'){
				matchingQuotesEnd = false;
			} else if(content[0] == '\"' && content[strlen(content) - 2] != '\"' ){
				matchingQuotesEnd = false;
			} else if(content[0] != '\"' && content[strlen(content) - 2] == '\"'){
				matchingQuotesEnd = false;
			} // end else if
		} else if(index == numberOfColumns){
			if(strlen(content) == 2 && content[0] == '\"'){
				matchingQuotesEnd = false;
			} else if(content[0] == '\"' && content[strlen(content) - 2] != '\"' ){
				matchingQuotesEnd = false;
			} else if(content[0] != '\"' && content[strlen(content) - 2] == '\"'){
				matchingQuotesEnd = false;
			} // end else if
		} else {
			if(strlen(content) == 1 && content[0] == '\"'){
				matchingQuotesEnd = false;
			} else if(content[0] == '\"' && content[strlen(content) - 1] != '\"' ){
				matchingQuotesEnd = false;
			} else if(content[0] != '\"' && content[strlen(content) - 1] == '\"'){
				matchingQuotesEnd = false;
			} // end else if
		}
	} else {
		if (isAtLastRow == true){
			if(strlen(content) == 1 && content[0] == '\"'){
				matchingQuotesEnd = false;
			} else if(content[0] == '\"' && content[strlen(content) - 1] != '\"' ){
				matchingQuotesEnd = false;
			} else if(content[0] != '\"' && content[strlen(content) - 1] == '\"'){
				matchingQuotesEnd = false;
			} // end else if
		} else if(index == numberOfColumns){
			if(strlen(content) == 3 && content[0] == '\"'){
				matchingQuotesEnd = false;
			} else if(content[0] == '\"' && content[strlen(content) - 3] != '\"' ){
				matchingQuotesEnd = false;
			} else if(content[0] != '\"' && content[strlen(content) - 3] == '\"'){
				matchingQuotesEnd = false;
			} // end else if
		} else {
			if(strlen(content) == 1 && content[0] == '\"'){
				matchingQuotesEnd = false;
			} else if(content[0] == '\"' && content[strlen(content) - 1] != '\"' ){
				matchingQuotesEnd = false;
			} else if(content[0] != '\"' && content[strlen(content) - 1] == '\"'){
				matchingQuotesEnd = false;
			} // end else if
		} // end else 
	} // end else
	return matchingQuotesEnd;
} // end checkHeaderContentEndQuoteMatching function

/*
	Determines if body content has matching quote or no quote format to its respective header column
	For example --> True
	"name"
	"Casey"

	For example --> True
	name
	Casey

	For example --> False
	"name"
	Casey

	For example --> False
	name
	"Casey"
*/
bool checkHeaderContentQuoteMatching(char* content, bool* headerSurroundedByQuotes, int index, int numberOfColumns, bool isAtLastRow){
	bool indexHasQuotes = headerSurroundedByQuotes[index];
	bool contentWrappedQuotes = false;

	if(content[strlen(content) - 1] == '\n' && content[strlen(content) - 2] != '\r'){
		if (isAtLastRow == true){
			if(content[0] == '\"' && content[strlen(content) - 2] == '\"' ){
				contentWrappedQuotes = true;
			} // end if
		} else if(index == numberOfColumns){
			if(content[0] == '\"' && content[strlen(content) - 2] == '\"' ){
				contentWrappedQuotes = true;
			} // end if
		} else {
			if(content[0] == '\"' && content[strlen(content) - 2] == '\"' ){
				contentWrappedQuotes = true;
			} // end if
		} // end else
	} else {
		if (isAtLastRow == true){
			if(content[0] == '\"' && content[strlen(content) - 1] == '\"' ){
				contentWrappedQuotes = true;
			} // end if
		} else if(index == numberOfColumns){
			if(content[0] == '\"' && content[strlen(content) - 3] == '\"' ){
				contentWrappedQuotes = true;
			} // end if
		} else {
			if(content[0] == '\"' && content[strlen(content) - 1] == '\"' ){
				contentWrappedQuotes = true;
			} // end if
		} // end else
	} // end else

	if (indexHasQuotes){
		if (contentWrappedQuotes == false){
			// if the header has surrounding quotes, but the text is not wrapped in quotes
			return false;
		} else {
			// if the header has surrounding quotes, and the text is wrapped in quotes
			return true;
		}
	}

	if (indexHasQuotes == false){
		if (contentWrappedQuotes){
			// if the header does not have surrounding quotes, but the text is wrapped in quotes
			return false;
		} else {
			// if the header does not have surrounding quotes, but the text is not wrapped in quotes
			return true;
		}
	}
	return NULL; // should never reach this point
} //end checkHeaderContentQuoteMatching function


/*
	Determines line validity.
	Calls helper functions to returns whether or not the line has matching end quotes and follows its' header's surrounded by quotes pattern
	numberOfColumns represents from 1 ->, not the index value
*/
bool checkLineValidity(char* line, bool* headerSurroundedByQuotes, int numberOfColumns, bool isAtLastRow){
	bool validLine = true;
	int column = -1;
	char* t = line;
	char tempString[1024] = "";

	//Goes through every character in line
	for (t = line; *t != '\0'; t++){
		//If current character is a comma
		if (*t == ','){
			column += 1;

			//Check if matching end quotes and follows header's pattern
			bool contentIsValid = checkHeaderContentQuoteMatching(tempString, headerSurroundedByQuotes, column, numberOfColumns-1, isAtLastRow);
			bool contentHasValidQuotes = checkHeaderContentEndQuoteMatching(tempString, headerSurroundedByQuotes, column, numberOfColumns-1, isAtLastRow);
			if(contentIsValid == false || contentHasValidQuotes == false){
				return false;
			}//end if
			tempString[0] = '\0';
		} else { 
			// build to the tempString
			int len = strlen(tempString);
			if (*t != '\0'){ 
				// chararcter not a end character
				tempString[len] = *t;
				tempString[len+1] = '\0';
			} else {
				 //character is end character
				tempString[len] = '\0';
			} //end else
		} // end else current character is not a comma
	} // end for loop

	//Check if matching end quotes and follows header's pattern
	bool finalcontentIsValid = checkHeaderContentQuoteMatching(tempString, headerSurroundedByQuotes, column + 1, numberOfColumns-1, isAtLastRow);
	bool finalcontentHasValidQuotes = checkHeaderContentEndQuoteMatching(tempString, headerSurroundedByQuotes, column + 1, numberOfColumns-1, isAtLastRow);
	if(finalcontentIsValid == false || finalcontentHasValidQuotes == false){
		return false;
	} //end if

	// Make sure there is the correct number of columns
	if (column + 2 > numberOfColumns || column + 2 < numberOfColumns){ //ensures must == +2
		// Invalid Input Format
		validLine = false;
	} //end if

	return validLine;
}//end function

/*
	If there is only a header row in the CSV..
	Returns the index of header column called name or "name"
	If it returns -1, then the header row is invalid somehow
*/
int singleRowHeaderValidityCheck(char* line, bool isAtLastRow){
	int column = -1; //Current column number
	int index = -1; //Index of header called name or "name"
	int counter = 0; //Current index (column) for headerNames array
	int countNames = 0; //Counts number of headers called name or "name"
	char* t = line;
	char tempString[1024] = "";

	char headerNames[1024][1024] = {};// max number of strings = 1024, max length of a string = 1024
	int numberBlankHeadersFound = 0; //Number of blank headers found, needs to be one or zero to be valid

	// Goes through every character in line
	for (t = line; *t != '\0'; t++){
		// If current chararcter is a comma
		if (*t == ','){
			column += 1;
			//Check if it has matching quotes on end
			if(checkMatchingEndQuotes(tempString) == false){
				// Invalid Input Format
				return -1;
			} // end if

			// If first and last character is " then remove
			if(tempString[0] == '\"' && tempString[strlen(tempString) - 1] == '\"' ){
				// First character is double quote
				// Remove first character
				for(int i = 1; i < strlen(tempString); i++){
					tempString[i-1] = tempString[i];
				} // end for loop
				tempString[strlen(tempString) - 1] ='\0';

				//Remove last character
				tempString[strlen(tempString) - 1] = '\0';
			} // end if statement

			// After removing outer quotes, check if the column name is a duplicate.
			if (strlen(tempString) == 0){
				if (numberBlankHeadersFound >= 1){
					// Invalid Input Format
					return -1;
				} // end if
				numberBlankHeadersFound += 1;
			} else {
				// Compare current String to previous Strings
				for (int i = 0; i < 1024; i++){
					if (strcmp(headerNames[i], tempString) == 0){
						// duplicate column name found
						// Invalid Input Format
						return -1;
					} // end if
				} // end for loop
			} // end else not a blank string

			// If reached this point then duplicate header was not found
			// Therefore add tempString to headerNames array
			for (int i = 0; i < strlen(tempString); i++){
				headerNames[counter][i] = tempString[i];
			} // end for loop

			// If string before comma is name
			if (strcmp(tempString, "name") == 0){
				countNames += 1;
				index = column;
				if (countNames > 1){
					//Output invalid
					// Invalid Input Format
					return -1;
				} // end if
				tempString[0] = '\0';
			} else {
				// String before comma is not name
				tempString[0] = '\0';
			} // end else

			// Increment current column number of headerNames array
			counter += 1;
		}else{
			// Add to tempString character, not a comma ","
			int len = strlen(tempString);

			if (*t != '\0'){ 
				// chararcter not a end character
				tempString[len] = *t;
				tempString[len+1] = '\0';
			} else { 
				// character is end character
				tempString[len] = '\0';
			} // end else
		} // end else current character not a comma
	}//end for loop

	bool matchingQuotesEndLastString = true;

	// Check if last string has matching quote ends
	if(strlen(tempString) == 1 && tempString[0] == '\"'){
		matchingQuotesEndLastString = false;
	}else if(tempString[0] == '\"' && tempString[strlen(tempString) - 1] != '\"' ){
		matchingQuotesEndLastString = false;
	}else if(tempString[0] != '\"' && tempString[strlen(tempString) - 1] == '\"'){
		matchingQuotesEndLastString = false;
	} // end else if

	// If not matching quote ends, then invalid
	if(matchingQuotesEndLastString == false){
		// Invalid Input Format
		return -1;
	} // end if

	// If sourrounded by quotes eliminate outside quotes
	if(tempString[0] == '\"' && tempString[strlen(tempString) - 1] == '\"' ){
		// First character is double quote
		// Remove first character
		for(int i = 1; i < strlen(tempString) - 1; i++){
			tempString[i-1] = tempString[i];
		} // end for loop
		tempString[strlen(tempString) - 1] ='\0';
		tempString[strlen(tempString) - 1] ='\0';
	} // end if statement

	// Compare last string to previous headers to find duplicates
	if (strcmp(tempString,"\0") == 0){ 
		if (numberBlankHeadersFound >= 1){
			// Invalid Input Format
			return -1;
		} // end if
		numberBlankHeadersFound += 1;
	} else {
		// Compare last string to previous headers to find duplicates
		for (int i = 0; i < 1024; i++){
			if (strcmp(headerNames[i], tempString) == 0){
				// duplicate column name found
				// Invalid Input Format
				return -1;
			} // end if
		} // end for loop
	} //end else

	column += 1;

	//See if last string is called name
	if(strcmp(tempString, "name") == 0){
		countNames += 1;
		index = column;
		if (countNames > 1){
			// Invalid Input Format
			return -1;
		} // end if
	} // end if
	return index;
} // end function

/*
	Used when there is additional rows aside from the header.e
	Returns the index of header column called name or "name"
	If it returns -1, then the header row is invalid somehow
	It also "returns" the number of columns fro the header row
*/
int retrieveNameIndex(char* line, bool ** headerSurroundedByQuotes, int * numberOfColumns, bool isAtLastRow){
	int index = -1; //Index of the header column called name or "name"
	int column = -1; //Current column number
	char* t = line;
	char tempString[1024] = "";
	int countNames = 0; //Counts the number of columns called name or "name", needs to be one to be valid
	int counter = 0; //Cuurent index (column) for headerNames array
	char headerNames[1024][1024] = {}; // max number of strings = 1024, max length of a string = 1024
	int numberBlankHeadersFound = 0; //Number of blank headers found, needs to be one or zero to be valid

	// Eliminate '\r' or '\n' if they exist
	if(line[strlen(line) - 1] == '\n'){
		line[strlen(line)- 1] = '\0';
	}//end if statement
	if(line[strlen(line) - 2] == '\r'){
		line[strlen(line) - 2] = '\0';
	} // end if statement

	// For every character in the line
	for (t = line; *t != '\0'; t++){
		// If character is comma
		if (*t == ','){
			// Increment current column number
			column += 1;
			// Check if it has matching quotes on end
			if(checkMatchingEndQuotes(tempString) == false){
				// Invalid Input Format
				return -1;
			} // end if

			// If first and last character is " then remove quotes
			if(tempString[0] == '\"' && tempString[strlen(tempString) - 1] == '\"' ){
				// Set the current column boolean to be true because it is surrounded by wuotes
				(*headerSurroundedByQuotes)[column] = true;

				// First character is double quote
				// Remove first character
				for(int i = 1; i < strlen(tempString); i++){
					tempString[i-1] = tempString[i];
				}
				tempString[strlen(tempString) - 1] ='\0';

				// Remove last character
				tempString[strlen(tempString) - 1] = '\0';
			} // end if statement

			// After removing outer quotes, check if the column name is a duplicate.
			if (strlen(tempString) == 0){
				// Then tempString is considered a blank	
				if (numberBlankHeadersFound >= 1){
					// Invalid Input Format
					return -1;
				} // end if
				numberBlankHeadersFound += 1;
			} else  {
				// Tempstring is not a blank
				// Check if current header matches any previous headers
				for (int i = 0; i < 1024; i++){
					if (strcmp(headerNames[i], tempString) == 0){
						// duplicate column name found
						// Invalid Input Format
						return -1;
					}//end if
				}//end for loop
			}//end else
			
			// If reached this point then duplicate header was not found
			// Therefore add tempString to headerNames array
			for (int i = 0; i < strlen(tempString); i++){
				headerNames[counter][i] = tempString[i];
			}//end for loop

			//If string before comma is name
			if (strcmp(tempString, "name") == 0){
				countNames += 1;
				index = column;
				if (countNames > 1){
					//Output invalid
					// Invalid Input Format
					return -1;
				} // end if
				tempString[0] = '\0';
			} else {
				// String before comma is not name
				tempString[0] = '\0';
			} // end else
			counter += 1;
		} else {
			 // Add to tempString character, not a comma ","
			int len = strlen(tempString);

			if (*t != '\0'){ 
				// chararcter not a end character
				tempString[len] = *t;
				tempString[len+1] = '\0';
			} else { //character is end character
				tempString[len] = '\0';
			} // end else
		} // end else not a comma
	} // end for loop

	bool matchingQuotesEndLastString = true;

	// If last character is return character
	if(tempString[strlen(tempString) -1] == '\r'){
		// Check for matching end quotes on the last string of the line
		if(strlen(tempString) == 2 && tempString[0] == '\"'){
			// If tempString is single quote
			matchingQuotesEndLastString = false;
		} else if(tempString[0] == '\"' && tempString[strlen(tempString) - 2] != '\"' ){
			matchingQuotesEndLastString = false;
		} else if(tempString[0] != '\"' && tempString[strlen(tempString) - 2] == '\"'){
			matchingQuotesEndLastString = false;
		} // end else if
	}else{
		//Check for matching end quotes on the last string of the line
		if(strlen(tempString) == 1 && tempString[0] == '\"'){
			//If tempString is single quote
			matchingQuotesEndLastString = false;
		} else if(tempString[0] == '\"' && tempString[strlen(tempString) - 1] != '\"' ){
			matchingQuotesEndLastString = false;
		} else if(tempString[0] != '\"' && tempString[strlen(tempString) - 1] == '\"'){
			matchingQuotesEndLastString = false;
		}//end else if
	}//end else
	
	// If there is not a matching end quote then invalid header
	if(matchingQuotesEndLastString == false){
		// Invalid Input Format
		return -1;
	} // end if statement

	// If last string is surrounded by quotes then remove quotes and say true for array
	if(tempString[strlen(tempString) -1] == '\r'){
		if(tempString[0] == '\"' && tempString[strlen(tempString) - 2] == '\"' ){
			// First character is double quote
			// Remove first character
			(*headerSurroundedByQuotes)[column+1] = true;
			for(int i = 1; i < strlen(tempString) - 1; i++){
				tempString[i-1] = tempString[i];
			} // end for loop
			tempString[strlen(tempString) - 2] ='\0';

			//Remove last character
			tempString[strlen(tempString) - 1] = '\r';		
		} // end if statement
	} else {
		if(tempString[0] == '\"' && tempString[strlen(tempString) - 1] == '\"' ){
			// First character is double quote
			// Remove first character
			(*headerSurroundedByQuotes)[column+1] = true;
			for(int i = 1; i < strlen(tempString); i++){
				tempString[i-1] = tempString[i];
			} //end ofr loop
			tempString[strlen(tempString) - 1] ='\0';
			
			//Remove last character
			tempString[strlen(tempString) - 1] = '\r';		
		} // end if statement
	} // end else statement

	// Compare last string to previous header columns to find a duplicate
	if (strcmp(tempString,"\r") == 0){ //check if last character is the carriage return
		if (numberBlankHeadersFound >= 1){
			// Invalid Input Format
			return -1;
		} // end if
		numberBlankHeadersFound += 1;
	} else {
		if(tempString[strlen(tempString)-1] == '\r'){
			tempString[strlen(tempString)-1] = '\0';
		}//end if

		//Compare last string to previous headers
		for (int i = 0; i < 1024; i++){
			if (strcmp(headerNames[i], tempString) == 0){
				// duplicate column name found
				// Invalid Input Format
				return -1;
			}//end if
		}//end for loop
	}//end else 

	column += 1;
	//Check if last string is name
	if(strcmp(tempString, "name") == 0){
		countNames += 1;
		index = column;
		if (countNames > 1){
			// Invalid Input Format
			return -1;
		}//end if
	}//end if
	*numberOfColumns = column;

	return index;
}//end function

/*
Returns the tweeter username from the line based off of the targetInd given
targetInd is the index of the column with the header named name or "name"
*/
char* retrieveTweeterFromLine(char* line, int targetInd){
	int counter = 0; //Counts the current column number
	char tempString[1024] = ""; //Holds the temporary string before a comma
	char* res = NULL; //Result string
	char* t = line; 
	//Goes through each character of line
	for (t = line; *t != '\0'; t++){
		//If current character is a comma
		if (*t == ','){
			//If current column number is the targetInd
			if (counter == targetInd){
				//Found the tweeter username, break from the for loop
				res = tempString;
				break;
			}//end if statement
			//Not the correct column, restart tempString and increase column number
			tempString[0] = '\0';
			counter += 1;
		} else {
			//Current character is not a comma
			//Append to tempString with the current character
			int len = strlen(tempString); //Length of the tempString
			if (*t != '\0'){ 
				//chararcter not a end character
				tempString[len] = *t;
				tempString[len+1] = '\0';
			} else { //character is end character
				tempString[len] = '\0';
			}//end else
		}//end else current character is not a comma
	}//end for loop

	res = tempString;
	return res;
}//end retrieveNameIndex function


/*
	Appends Tweeter to the empty tweeterFrequency array 
*/
void appendTweeterToEmpty(char* tweeter, int tweeterInformationIndex, struct TweeterInformation** tweeterFrequency, bool isLastRow, int nameIndex, int numberOfColumns){
	struct TweeterInformation newTweeter = {
		.tweeter_username = (char *)malloc(sizeof(char) * (strlen(tweeter)+1)),
		.numberOfTweets = 1,
	};

	for(int i = 0; i < strlen(tweeter); i++){
		newTweeter.tweeter_username[i] = tweeter[i];
	} // end for loop
	newTweeter.tweeter_username[strlen(tweeter)] = '\0';
	
	// Update number of tweets to tweeterFrequency
	(*tweeterFrequency)[tweeterInformationIndex].numberOfTweets = newTweeter.numberOfTweets;
	
	if(newTweeter.tweeter_username[strlen(newTweeter.tweeter_username) -1] == '\n'){
		// If second to last character is '\r'
		if(newTweeter.tweeter_username[strlen(newTweeter.tweeter_username) -2] == '\r'){
			// Malloc size for tweeterFrequency.tweeter_username
			// Not including the '\r' and '\n' characters
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username = (char *)malloc(sizeof(char) * (strlen(newTweeter.tweeter_username)-2));
			for(int i = 0; i < strlen(newTweeter.tweeter_username) -2; i++){
				(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[i] = newTweeter.tweeter_username[i];
			} // end for loop
		}else{
			// Last character is '\n' and second last character is not '\r'
			// Malloc size for tweeterFrequency.tweeter_username
			// Not including the last character '\n'
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username = (char *)malloc(sizeof(char) * (strlen(newTweeter.tweeter_username)-1));
			for(int i = 0; i < strlen(newTweeter.tweeter_username) -1; i++){
				(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[i] = newTweeter.tweeter_username[i];
			} // end for loop
		}//end else statement
	} else{
		//Last character is not '\n'
		if(isLastRow == true){
			// If last row and last character of username is not '\n'
			// Then username must not be the last column of the last row
			// Therefore collect entire username
			// Malloc size for tweeterFrequency.tweeter_username
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username = (char *)malloc(sizeof(char) * strlen(newTweeter.tweeter_username));
			for(int i = 0; i < strlen(newTweeter.tweeter_username); i++){
				(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[i] = newTweeter.tweeter_username[i];
			} // end for loop
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[strlen(newTweeter.tweeter_username)] = '\0';
		} else if(nameIndex == numberOfColumns){
			// If last column and not last row and last character of username is not '\n'
			// Malloc size for tweeterFrequency.tweeter_username
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username = (char *)malloc(sizeof(char) * (strlen(newTweeter.tweeter_username)-2));
			for(int i = 0; i < strlen(newTweeter.tweeter_username)-2; i++){
				(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[i] = newTweeter.tweeter_username[i];
			} // end for loop
		} else{
			// If not last row and not last column and not end in '\n'
			// Then collect entire username
			// Malloc size for tweeterFrequency.tweeter_username
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username = (char *)malloc(sizeof(char) * strlen(newTweeter.tweeter_username));
			for(int i = 0; i < strlen(newTweeter.tweeter_username); i++){
				(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[i] = newTweeter.tweeter_username[i];
			} // end for loop
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[strlen(newTweeter.tweeter_username)] = '\0';
		} // end else statement
	} // end else statement not end in '\n' character
	free(newTweeter.tweeter_username);
} //end appendTweeterToEmpty function

/*
	Helper function to check if the Tweeter exists in the TweeterFrequency array
	Returns -1 if tweeter does not exist in array
	Returns index otherwise
*/
int checkIfTweeterExistsInFrequency(int tweeterInformationIndex, char* tweeter, struct TweeterInformation* tweeterFrequency){
	int tweeterIndex = -1;
	for (int i = 0; i < tweeterInformationIndex; i++){
		char * compTemp;
		// If last two characters are "\r\n"
		if( tweeter[strlen(tweeter) - 1] == '\n' && tweeter[strlen(tweeter) - 2] == '\r'){
			// Do not include last two characters
			// Malloc size for compTemp
			compTemp= (char *)malloc(sizeof(char) * (strlen(tweeter) - 2));
			for(int x = 0; x < strlen(tweeter) - 2; x++){
				compTemp[x] = tweeter[x];
			} // end for loop
		} else if(tweeter[strlen(tweeter) - 1] == '\n'){
			// If last character is '\n' and second to last character is not '\r'
			// Do not include last character
			// Malloc size for compTemp
			compTemp = (char *)malloc(sizeof(char) * (strlen(tweeter)-1));
			for(int x = 0; x < strlen(tweeter)-1; x++){
				compTemp[x] = tweeter[x];
			} // end for loop
		}else{
			// If last character is not '\n' or "\r\n"
			// Then collect all the characters from the tweeter string
			// Malloc size for compTemp
			compTemp = (char *)malloc(sizeof(char) * (strlen(tweeter)));
			for(int x = 0; x < strlen(tweeter); x++){
				compTemp[x] = tweeter[x];
			} // end for loop
		} // end else

		// If compTemp is equal to the tweeter username at index i of TweeterInformation Array
	 	if (strcmp(tweeterFrequency[i].tweeter_username, compTemp) == 0){
	 		// Then current tweeter already exists
	 		// And set index of duplicate tweeter to i
			tweeterIndex = i;
			free(compTemp);
			// Exit out of for loop
			break;
	 	} // end if statement	
	 	free(compTemp);
	} // end for loop comparing TweeterInformation usernames to current Tweeter
	return tweeterIndex;
} // end checkIfTweeterExistsInFrequency function

/*
	If tweeterFrequency is not empty, this function adds the tweeter to the tweeterFrequency array.
*/
void addNewTweeterToNonEmptyFrequency(char* tweeter, struct TweeterInformation** tweeterFrequency, int tweeterInformationIndex, bool isLastRow, int nameIndex, int numberOfColumns){
	// Tweeter does not exist in TweeterFrequency, so add it to the TweeterFrequency Array
	// Realloc the tweeterFrequency array to plus one its current size
	
	// Malloc size for tweeterFrequency.tweeter_username
	struct TweeterInformation newTweeter = {
			.tweeter_username = (char *)malloc(sizeof(char) * (strlen(tweeter)+1)),
			.numberOfTweets = 1,
	};
	for(int i = 0; i < strlen(tweeter); i++){
		newTweeter.tweeter_username[i] = tweeter[i];
	} // end for loop
	newTweeter.tweeter_username[strlen(tweeter)] = '\0';

	// Malloc size for tweeterFrequency.tweeter_username
	// If last character is '\n'
	if(newTweeter.tweeter_username[strlen(newTweeter.tweeter_username) -1] == '\n'){
		// If second to last character is '\r'
		if(newTweeter.tweeter_username[strlen(newTweeter.tweeter_username) -2] == '\r'){
			// Then skip last two characters for TweeterInformation array
			// Malloc size of username at last spot in TweeterInformation array
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username = (char *)malloc(sizeof(char) * (strlen(newTweeter.tweeter_username)-2));
			for(int i = 0; i < strlen(newTweeter.tweeter_username) -2; i++){
				(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[i] = newTweeter.tweeter_username[i];
			} // end for loop
		}else{
			// Second to last character is not '\r'
			// Then skip last character '\n'
			// Malloc size of username at last spot in TweeterInformation array
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username = (char *)malloc(sizeof(char) * (strlen(newTweeter.tweeter_username)-1));
			for(int i = 0; i < strlen(newTweeter.tweeter_username) -1; i++){
				(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[i] = newTweeter.tweeter_username[i];
			} // end for loop
		} // end else statement
	}else{
		// Last character is not '\n'
		if(isLastRow == true){
			// If last row and last character of username is not '\n'
			// Then username must not be the last column of the last row
			// Therefore collect entire username
			// Malloc size for tweeterFrequency.tweeter_username
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username = (char *)malloc(sizeof(char) * strlen(newTweeter.tweeter_username));
			for(int i = 0; i < strlen(newTweeter.tweeter_username); i++){
				(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[i] = newTweeter.tweeter_username[i];
			} // end for loop
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[strlen(newTweeter.tweeter_username)] = '\0';
		}else if(nameIndex == numberOfColumns){
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username = (char *)malloc(sizeof(char) * (strlen(newTweeter.tweeter_username)-2));
			for(int i = 0; i < strlen(newTweeter.tweeter_username)-2; i++){
				(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[i] = newTweeter.tweeter_username[i];
			} // end for loop
		}else{
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username = (char *)malloc(sizeof(char) * strlen(newTweeter.tweeter_username));
			for(int i = 0; i < strlen(newTweeter.tweeter_username); i++){
				(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[i] = newTweeter.tweeter_username[i];
			} // end for loop
			(*tweeterFrequency)[tweeterInformationIndex].tweeter_username[strlen(newTweeter.tweeter_username)] = '\0';
		} // end else statement
	} // end else statement last character is not '\n'

	// Update number of tweets to tweeterFrequency
	(*tweeterFrequency)[tweeterInformationIndex].numberOfTweets = newTweeter.numberOfTweets;
	// Free newTweeter
	free(newTweeter.tweeter_username);
} // end addNewTweeterToNonEmptyFrequency function


/*
	Sorts and prints the top 10 tweeters based on numberOfTweets 
*/
void sortAndPrintTop10Tweeters(int tweeterInformationIndex, struct TweeterInformation* tweeterFrequency){
	// Array of the index of the tweeter in the TweeterInformation array in order based on number of tweets
	int * sortedNumberOfTweetersIndex = (int*)malloc(sizeof(int) * tweeterInformationIndex);
	for(int i = 0; i < tweeterInformationIndex; i++){
		sortedNumberOfTweetersIndex[i] = i;
	} // end for loop

	if(tweeterInformationIndex > 0 ){
		//At least one tweeter exists
		//Quick sorts by the number of tweets from TweeterINformation array
		top10(tweeterFrequency, &sortedNumberOfTweetersIndex, 0, tweeterInformationIndex-1);
		if(tweeterInformationIndex < 10){
			for(int i = tweeterInformationIndex - 1; i >= 0; i--){
				int id = sortedNumberOfTweetersIndex[i];
				if (tweeterFrequency[id].tweeter_username[0] == '\"' && tweeterFrequency[id].tweeter_username[strlen(tweeterFrequency[id].tweeter_username) - 1] == '\"'){
					for (int j = 1; j < strlen(tweeterFrequency[id].tweeter_username) -1; j++){
						printf("%c",tweeterFrequency[id].tweeter_username[j]);
					}
					printf(": %d\n", tweeterFrequency[id].numberOfTweets);
				} else {
					printf("%s: %d\n", tweeterFrequency[id].tweeter_username, tweeterFrequency[id].numberOfTweets);
				}
			}//end for loop
		}else{
			int index = tweeterInformationIndex -1;
			for(int i = 9; i >= 0; i--){
				int id = sortedNumberOfTweetersIndex[index];
				if (tweeterFrequency[id].tweeter_username[0] == '\"' && tweeterFrequency[id].tweeter_username[strlen(tweeterFrequency[id].tweeter_username) - 1] == '\"'){
					for (int j = 1; j < strlen(tweeterFrequency[id].tweeter_username) -1; j++){
						printf("%c",tweeterFrequency[id].tweeter_username[j]);
					}
					printf(": %d\n", tweeterFrequency[id].numberOfTweets);
				} else {
					printf("%s: %d\n", tweeterFrequency[id].tweeter_username, tweeterFrequency[id].numberOfTweets);
				}
				index--;
			} // end for loop
		} // end else
	} // end if 
	free(sortedNumberOfTweetersIndex);
} // end sortAndPrintTop10Tweeters function

int main(int argc, char** argv) {

	mustExitProgram = false;
	//Check if there are only 2 arguments from command line
	if (argc > 2 || argc < 2){
		// Invalid Input Format
		mustExitProgram = true;
	}//end if statement


	//Check if file ends in .csv
	if (mustExitProgram == false){
		int lengthOfInputArgument = strlen(argv[1]);
		if(lengthOfInputArgument < 5){ //last 4 characters are .csv need at least one more character
			// Invalid Input Format
			mustExitProgram = true;
		}else{
			//Check if last 4 are .csv
			const char *lastFourCharacters = &(argv[1])[lengthOfInputArgument-4];
			if(strcmp(lastFourCharacters, ".csv") != 0){
				// Invalid Input Format
				mustExitProgram = true;
			}//end if 
		}//end else
	}

	FILE *stream = fopen(argv[1], "r");

	//Check if .csv  file exists
	if (mustExitProgram == false) {
		if(stream == NULL){
			// Invalid Input Format
			mustExitProgram = true;
		}//end if statement
	}
	
	char line[1026]; //Holds a row of a file
	int counter = 1; //Current row number
	int numberOfColumns = 0; //Number of columns based from header row
	bool *headerSurroundedByQuotes = (bool *) malloc(sizeof(bool) * 1024); //Array of booleans for each column in header if surrounded by quotes
	struct TweeterInformation *tweeterFrequency = malloc(sizeof(struct TweeterInformation)); //Array of TweeterInformation

	//Initialize the array of booleans to false
	for (int i=0; i<1024; ++i) {
		headerSurroundedByQuotes[i] = false;
	}//end for loop
    
	int numberOfRows=0;
	FILE *stream2 = fopen(argv[1], "r");

	if (mustExitProgram == false){
		char c = getc(stream2);
		//Count number of rows which is indicated by '\n' character
		if(c != EOF){
			while(c != EOF){
				//If character is new line then increment number of rows by 1
				if(c == '\n'){
					numberOfRows++;
					c = getc(stream2);
					//Next character is end of line then 
					//Decrement number of rows by one
					if(c == EOF){
						numberOfRows--;
					}//end if statement
				}else{
					c = getc(stream2);
				}//end else statment
			}//end while loop
			numberOfRows++;
		}//end if statement
	}

	//If number of rows is 0 then invalid
	if(numberOfRows == 0){
		// Invalid Input Format
		mustExitProgram = true;
	}//end if statement

	//If number of rows is > 20000 then invalid
	if (numberOfRows > 20000){
		// Invalid Input Format
		mustExitProgram = true;
	}//end if statement

	int nameIndex = -1; //Index which has name or "name" as the header's name from the header row
	int tweeterInformationIndex = 0; //Number of entries in TweeterInformation array
	bool previousOverflow = false; //Boolean if previous row had overflow from too many characters
	bool headerRow = true; //Boolean if row is header row

	//Gets every individual row called line

	while (fgets(line, 1026, stream)){
		if (mustExitProgram == false){
			if(headerRow == true){
				// NOTE: MAX number of "actual" characters in a line can be 1022, so that 2 more characters can be the '\r' and '\n'.
				//Check if header has more than 1024 characters then invalid
				if (strlen(line) > 1024){ // including carriage return & new lines
					// Invalid Input Format
					mustExitProgram = true;
				} else {
					//If there is only one row in the file
					if(numberOfRows == 1){
						// Get nameIndex to check the validity of the header
						nameIndex = singleRowHeaderValidityCheck(line, true);
					}else{
						// If there is more than one row, retrieve the index of "name" to check validity of the header
						nameIndex = retrieveNameIndex(line, &headerSurroundedByQuotes, &numberOfColumns, false);
					}//end else statement

					//If could not find a header column named name or "name" then invalid
					if(nameIndex == -1){
						// Invalid Input Format
						mustExitProgram = true;
						continue;
					} //end if statement
				}//end else statement <= 1024 characters
				headerRow = false;
			}//end if statement headerRow == true
			else {
				//Skips over rows that are >1024 characters including overflow rows that are >1025
				if(strlen(line) == 1025 && (previousOverflow == true)){
					//Here if current line >1024 characters and previous line overflowed
					//Therefore do not increment counter, still the same row
					//And skip to the next row

					//If end of the line is new line character then
					//The line is done and will not overflow 
					if(line[1024] == '\n'){
						previousOverflow = false;
					}else{
						previousOverflow = true;
					}//end else statement

					//Skip to get next line for while loop
					continue;
				}else if(strlen(line) == 1025 && (previousOverflow == false)){
					//Here if current line > 1024 characters and previous line did not overflow
					//Therefore increment counter because it is a new row
					//And skip to the next row
					counter++;

					//If end of the line is new line character then
					//The line is done and will not overflow 
					if(line[1024] == '\n'){
						previousOverflow = false;
					}else{
						previousOverflow = true;
					}//end else statement

					//Skip to get next line for while loop
					continue;
				}else if(strlen(line) <= 1024 && (previousOverflow == true)){
					//Here if current line <= 1024 characters and previous line overflowed
					//Therefore do not increment counter, still the same row
					//And skip next row

					//This row will not overflow to the next one, so set to false
					previousOverflow = false;

					//Skip to get next line for while loop
					continue;
				}else{
					//Here if current line <= 1024 characters and previous line did not overflow to this line
					//Therefore increment counter because it is a new row
					//Leave previousOverflow false

					counter++;
				}//end else statement length of row check

				int len = strlen(retrieveTweeterFromLine(line,nameIndex)); //Length of the tweeter username from nameIndex

				//Malloc size for the tweeter username array
				char* tweeter = (char *)malloc(sizeof(char) * (strlen(retrieveTweeterFromLine(line, nameIndex)) + 1)) ;
				for(int i = 0; i < len; i++){
					tweeter[i] = (retrieveTweeterFromLine(line,nameIndex))[i];
				}//end for loop
				tweeter[len] = '\0';

				//If no tweeter usernames in the TweeterInformation array yet
				if(tweeterInformationIndex == 0){
					
					bool isLastRow = false; //If row is the last row of the file
					//Last row if current row number equals number of rows
					if (counter == numberOfRows){
						isLastRow = true;
					}//end if statement

					//Check the validity of the current line 
					bool valid = checkLineValidity(line, headerSurroundedByQuotes, numberOfColumns+1, isLastRow);

					//If the line is valid
					if (valid){
						appendTweeterToEmpty(tweeter, tweeterInformationIndex, &tweeterFrequency, isLastRow, nameIndex, numberOfColumns);
						//Increment number of tweeters in TweeterInformation array
						tweeterInformationIndex++;
					}//end if statement is valid line
				}//end if first tweeter name
				else{
					//Not the first tweeter
					bool isLastRow = false;//If row is the last row of the file
					//Last row if current row number equals number of rows
					if (strlen(line) <= 1024) {
						isLastRow = false;
						if (counter == numberOfRows){
							isLastRow = true;
						}//end if statement
					}

					//Check validity of current line
					bool valid = checkLineValidity(line, headerSurroundedByQuotes, numberOfColumns+1, isLastRow);

					//If the line is valid
					if (valid == true){
						//Compare strings in tweeterFrequency to current tweeter name
						int tweeterIndex = -1;
						tweeterIndex = checkIfTweeterExistsInFrequency(tweeterInformationIndex, tweeter, tweeterFrequency);

						if(tweeterIndex != -1){
							// Increment number of tweets for tweeter name at tweeterIndex
							tweeterFrequency[tweeterIndex].numberOfTweets += 1;
							// Duplicate name so subtract one from tweeterInformationIndex
							tweeterInformationIndex = tweeterInformationIndex - 1;
						} // end if tweeter already exists
						else{
							// Tweeter does not exist, so add it to the TweeterInformation Array
							// Realloc the tweeterFrequency array to plus one its current size
							tweeterFrequency = realloc(tweeterFrequency, ((((sizeof(tweeterFrequency) +8)*(tweeterInformationIndex+1))/sizeof(struct TweeterInformation)) + 1) * sizeof(struct TweeterInformation));
							addNewTweeterToNonEmptyFrequency(tweeter, &tweeterFrequency, tweeterInformationIndex, isLastRow, nameIndex, numberOfColumns);
						} // end else tweeter does not exist in array
						// Increment the number of tweeters in TweeterInformation array
						tweeterInformationIndex++;
					} // end if valid line			
				} // end else not first tweeter
			} //end else not header row
		} // end if mustExitProgram
	} //end while loop

	if (mustExitProgram == true){
		printf("Invalid Input Format\n");
		exit(0);
	}

	sortAndPrintTop10Tweeters(tweeterInformationIndex, tweeterFrequency);

	//Free each of the char arrays in tweeterFrequency
	for(int i = 0; i < tweeterInformationIndex; i++){
		free(tweeterFrequency[i].tweeter_username);
	}//end for loop

	free(tweeterFrequency);
	free(headerSurroundedByQuotes);
	fclose(stream);
}//end main function