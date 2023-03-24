#include<iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <queue>

class Trie {
public:

	Trie() {
		root = new Node();
	}
	struct Node {
		Node* letter[26];
		int strings;

		Node() {
			strings = 0;
			for (int i = 0; i < 26; ++i) {
				letter[i] = nullptr;
			}
		}

	};


	void Add(std::string& word) {
		Node* currentpointer = root;
		for (int i = 0; i < word.length(); ++i) {
			char current = word[i];
			// current - 'a' -> номер буквы в кодировке
			if (currentpointer->letter[current - 'a'] == nullptr) {
				currentpointer -> letter[current - 'a'] = new Node();
			}
			currentpointer = currentpointer->letter[current - 'a'];
		}
		currentpointer -> strings++;
		
	};

	Node* Find(std::string& word) {
		Node* currentpointer = root;
		
		for (int i = 0; i < word.length(); ++i) {
			char current = word[i];
			currentpointer = currentpointer->letter[current - 'a'];
			if (currentpointer == nullptr) {
				return nullptr;
			}
		}
		return currentpointer;
	}

	void WriteEnds(Node* currentpointer, std::string& startWord, std::string& endsWord) {
		if (currentpointer == nullptr) {
			std::cout << "dont find" << std::endl;
			return;
		}
		if (currentpointer->strings > 0) {
			std::cout << startWord + endsWord << std::endl;
		}
		for (int i = 0; i < 26; ++i) {
			// ((char)) c - 'a' -> дает нам порядковый номер чара (int)
			// ((int) i) + 'a' -> даст нам char с порядковым номером относительно буквы 'a'
			if (currentpointer->letter[i] != nullptr) {
				endsWord.push_back('a' + i);
				WriteEnds(currentpointer->letter[i], startWord, endsWord);
				endsWord.pop_back();
			}
		}

	}
private:
	Node* root;
};


int main() {
	bool flag = false;
	int n;
	std::cin >> n;
	std::string cur_str = "";
	Trie* myTrie = new Trie();

	// вводим строки в "словарь" - в бор
	for (int i = 0; i < n; i++) {
		std::string s;
		std::cin >> s;
		myTrie->Add(s);
	}

	while (true)
	{
		std::cout << "\n";
		std::string s;
		std::cin >> s;
		while (true) {
			if (flag) {
				flag = false;
				break;
			}
			if (_kbhit()) // слушатель нажатия на клавиатуру
			{
				switch (_getch()) // ждёт нажатия на клавиатуру
				{
				case 13: // Отслеживает нажатие на Enter
					std::cout << "Possible words:" << std::endl;
					myTrie->WriteEnds(myTrie->Find(s), s, cur_str);
					flag = true;
					break;

				}
			}
		}
	}

	return 0;
}