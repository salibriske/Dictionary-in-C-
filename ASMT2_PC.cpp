//
//ASMT02_PC.cpp
//Tommy Tran
//Partner: Brandon Chen
//Due Date 10/18/18
//CSC340 Assignment 2C
//
#include <iostream>;
#include <fstream>;
#include <string>;
#include <vector>;
#include <algorithm>;
#include <utility>;
#include <tuple>;
using namespace std;

class entry;
class entry {
public:
	string key, def, part;
	entry(string key2, string part2, string def2) {// creates an entry with a key, a part of speech, and a definition
		key = key2;
		part = part2;
		def = def2;
	}


};
void toLowerCase(string& str);
void makeDictionary(vector<entry> &dictionary);
void sortDictionary(vector <entry> &dictionary);
void userInput(string input, string inputArray[]);
bool isDistinct(string input2);
bool isPart(string input2);
void searchPrint(vector<entry>dictionary, string inputArray[]);


void toLowerCase(string& str) {// sends all characters to lower case.
	for (int i = 0; i < str.length(); i++) {
		char c = str[i];
		if ('A' <= c && c <= 'Z') {
			str[i] += ('a' - 'A');// lowercase has a higher ascii value than uppercase, find difference, add it to char at i
		}
	}
}

void makeDictionary(vector<entry> &dictionary) {
	ifstream file;
	cout << "! Opening data file... ./Data.CS.SFSU.txt" << endl;	// print statements
	file.open("Data.CS.SFSU.txt");
	cout << "! Loading data..." << endl;
	cout << "! Loading completed..." << endl;
	cout << "! Closing data file... ./Data.CS.SFSU.txt" << endl;
	cout << endl;
	cout << " ----- DICTIONARY 340 C++ -----" << endl;
	char line[1000];

	while (file.getline(line, 1000)) {	//loops thought the file and puts data into entries
		string s = line;
		string bar = "|";
		int position;
		string arrow = "-=>>";
		string name = s.substr(0, position = s.find(bar)); // creates a copy of string words from bar from start to end
		s.erase(0, position + 1); // erases the word and the bar

		while ((position = s.find(bar)) != std::string::npos) {		// npos stops from looping if no more bars
			string def = s.substr(0, position);
			s.erase(0, position + bar.length()); 
			string part = def.substr(0, -1 + (position = def.find(arrow))); // -1 gets rid of a trailing space
			def.erase(0, position + arrow.length());		// erases both part and arrow
			dictionary.push_back(entry(name, part, def));
		}
		string def = s.substr(0, position);				// Prevents off By 1 error
		s.erase(0, position + bar.length());
		string part = def.substr(0, -1 + (position = def.find(arrow))); 
		def.erase(0, position + arrow.length()); 
		dictionary.push_back(entry(name, part, def));
	}
	file.close();
}
void sortDictionary(vector <entry> &dictionary) { // sorts the parts of speech alphabetically

	sort(dictionary.begin(), dictionary.end(), [](const entry& first, const entry& second) {// sort function for def
		return first.def < second.def;
	});
	sort(dictionary.begin(), dictionary.end(), [](const entry& first, const entry& second) {// sort function for part
		return first.part < second.part;
	});
}
void userInput(string input, string inputArray[]) {// detects user input and puts it into an array
	int position;
	string key = input.substr(0, (position = input.find(" ")));
	toLowerCase(key);
	string input2 = "";
	string input3 = "";
	if (position == -1) { // if only 1 word input
		input.erase(0, input.length());// erases
	}
	else {
		input.erase(0, position + 1);
		input2 = input.substr(0, (position = input.find(" ")));
		toLowerCase(input2);
		if (!isPart(input2) && !isDistinct(input2) && input2 !="" ) {// if second word is not distinct or a part of speech, changes second input to "bad"
			cout << "\t<2nd argument must be a part of speech or distinct>" << endl;
			input2 = "bad";
		}
		if (position == -1) { //if have 2 word input
			input.erase(0, input.length());
		}
		else {// if have 3 word input
			input.erase(0, position + 1);
			input3 = input.substr(0, (position = key.find(" ")));
			toLowerCase(input3);
		}
	}
	inputArray[0] = key;// stores user input into an array.
	inputArray[1] = input2;
	inputArray[2] = input3;

}
bool isDistinct(string input2) {// checks if input is distinct
	return (input2 == "distinct");
}
bool isPart(string input2) {// checks if input is part of speech
	return (input2 == "noun" || input2 == "verb" || input2 == "adjective" || input2 == "interjection"
		|| input2 == "conjunction" || input2 == "preposition" || input2 == "adverb" || input2 == "pronoun");
}
void searchPrint(vector<entry>dictionary, string inputArray[]) {// searches dictionary and prints entries
	string key = inputArray[0];
	string input2 = inputArray[1];
	string input3 = inputArray[2];
	vector<entry>::iterator search;
	entry previous("", "", "");// for checking if distinct
	if (input2 == "bad") {// exit if second input is "bad"
		return;
	}
	int found = 0;// if there is not printing, then prints "not found"
		for (search = dictionary.begin(); search != dictionary.end(); search++) {// for loop iterates through the dictionary
			entry input = *search;
			if (input.key == key) {// if the key matches
				if (isPart(input2)) {
					if (input.part == input2) {// if the part of speech matches
						if (isDistinct(input3)) {
							if (input.def != previous.def) { // if the definition is distinct
								cout << input.key << " [" << input.part << "] : " << input.def << endl;// if part of speech and distinct is entered
								previous = input;
								found++;
							}
						}
						else {
							cout << input.key << " [" << input.part << "] : " << input.def << endl;// if only part of speech is entered
							previous = input;
							found++;
						}
					}

				}
				else if (isDistinct(input2)) {
					if (input.part != previous.part || input.def != previous.def) {// prints the first of each part of speech and first of definition
						cout << input.key << " [" << input.part << "] : " << input.def << endl; // if distinct is only entered
						previous = input;
						found++;
					}
				}
				else {
					cout << input.key << " [" << input.part << "] : " << input.def << endl; // if only key is entered
					previous = input;
					found++;
				}

			}
		}

		if (found == 0) {// if no entries are printed
			cout << "\t<Not Found>" << endl;


	}
}

int main() {
	vector<entry> dictionary; // initialize dictionary
	makeDictionary(dictionary);// makes dictionary
	sortDictionary(dictionary);// sorts dictionary

	while (true) {
		char input[500];
		cout << "Search: " << flush;
		cin.getline(input, 500);// gets the user input
		string inputString(input);
		string inputArray[3]; // initializes user input
		if (inputString != "!Q") {
			cout << "\t|" << endl;
			userInput(inputString, inputArray); // checks the user input
			searchPrint(dictionary, inputArray);// searches and prings entries
			cout << "\t|" << endl;
		}
		else {// exits if !Q is entered
			cout << "-----THANK YOU!-----" << endl;
			break;
		}
	}
}