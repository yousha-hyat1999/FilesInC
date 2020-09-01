#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
	int processNested, nestedCmntFlag, countNested;
	FILE* filePointer;

	// in case file name is not given:
	/*if (argc < 2) {
		printf("Usage: no_cmnts [source-file-name] [-n (optional)]\n");
		return 0;
	}*/

	// bonus points part:
	/*if (argc == 3) {
		if (strcmp("-n", argv[2]) == 0) {
			processNested = 1;
		}
		else {
			printf("Usage: no_cmnts [source-file-name] [-n (optional)]\n");
			return -1;
		}
	}
	else
		processNested = 0;*/

	// open file and test if opened correctly
	/*filePointer = fopen(argv[1], "r");
	if (filePointer == NULL){
		printf("[Error] failed to open file '%s'\n", argv[1]);
		return -1;
	}*/
	char fileName[100];
	char choice;

	printf("Enter your file name: ");
	scanf("%s", &fileName);

	filePointer = fopen(fileName, "r");
	if (filePointer == NULL) {
		printf("[Error] failed to open file '%s'\n", fileName);
		return -1;
	}

	printf("[Bonus Part] Do you want to scan for nested comments (Y/N)? : ");
	scanf(" %c", &choice);

	if (choice == 'y' || choice == 'Y')
		processNested = 1;
	else
		processNested = 0;
	
	char c;
	// **** logic variables ****
	
	// keep track of string
	// pre-condition: assuming that code is correct
	// a string must start and end on same line
	int stringFlag = 0;	// initialized to false

	// keep track of one line comment
	//	0- no flag
	//	1- simple comment
	int oneLineCmntFlag = 0;	// initialized to no flag

	// commentFlag value meaning: 
	//	0- no flag
	//	1- multi-comment
	//	2- possible end of multiline comment detected
	int multiLineCmntFlag = 0;	// initialized to no flag

	// common flag for comments
	int cmntCommonFlag = 0;	// initialized to no flag

	if (processNested) {
		countNested = 0;
		nestedCmntFlag = 0;
	}

	do {
		// read text, process and print to console
		c = fgetc(filePointer);
		
		// if is a string AND not a comment
		if ((stringFlag || c == '"') && oneLineCmntFlag != 1 && multiLineCmntFlag != 1) {
			if (c == '"')
				stringFlag = !stringFlag;	// 1 to 0 and 0 to 1
		}

		if (!stringFlag) {

			if (processNested == 1 && multiLineCmntFlag == 1) {
				if (c == '/' && nestedCmntFlag == 0 && oneLineCmntFlag == 0) {
					nestedCmntFlag = 1;
					continue;
				}
				if (nestedCmntFlag == 1) {
					nestedCmntFlag = 0;
					if (c == '*') {
						countNested++;
					}
				}
			}

			if (c == '/' && cmntCommonFlag == 0 && oneLineCmntFlag == 0 && multiLineCmntFlag == 0) {
				cmntCommonFlag = 1;
				continue;
			}

			if (cmntCommonFlag == 1) {
				cmntCommonFlag = 0;
				if (c == '/') {
					oneLineCmntFlag = 1;
					continue;
				}
				else
				if (c == '*') {
					multiLineCmntFlag = 1;
					continue;
				}
				else {
					printf("/");
				}
			}

			if (c == '\n' && oneLineCmntFlag == 1) {
				oneLineCmntFlag = 0;
				printf("\n");
				continue;
			}

			if (c == '*' && multiLineCmntFlag == 1) {
				multiLineCmntFlag = 2;
				continue;
			}

			if (multiLineCmntFlag == 2) {
				if (c == '/') {
					if (processNested) {
						if (countNested == 0) {
							multiLineCmntFlag = 0;
							continue;
						}
						else {
							countNested--;
							multiLineCmntFlag = 1;
							continue;
						}
					}
					else {
						multiLineCmntFlag = 0;
						continue;
					}
				}
				else{
					multiLineCmntFlag = 1;
					continue;
				}
			}
		}

		
		if(oneLineCmntFlag != 1 && multiLineCmntFlag != 1)
			printf("%c", c);
	} while (c != EOF);

	fclose(filePointer);
	getchar();

	getchar();
	return 0;
}