#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct Node
{
	int ID; // ID for website
	string URL[53]; // Size 200 is by default for URL of the link
	string keyword;//keywords on the second line
	Node* left; // Pointer to the left subtree of a node
	Node* right; // Pointer to the right subtree of a node
	Node()
	{
		ID = 0;
		keyword = " ";
		left = NULL;
		right = NULL;
		for (int i = 0; i < 53; i++)
		{
			URL[i] = "";
		}
	}
	Node(int id, string link, string line)
	{
		this->ID = id;
		keyword = line;
		this->left = NULL;
		this->right = NULL;
		int i = 0;
		while (URL[i]!="")
		{
			i++;
		}
		URL[i] = link;

	}
	~Node()
	{
		if (left != NULL)
		{
			delete left;
			left = nullptr;
		}
		if (right != NULL)
		{
			delete right;
			right = nullptr;
		}
	}
	string* getURL()
	{
		return URL;
	}
};
class AVL
{
private:
	Node* root; // Pointer to the root node of the BST
public:
	void setroot(Node* n)
	{
		root = n;
	}
	AVL() // Default constructor
	{
		root = nullptr;
	}
	~AVL()
	{
		if (root != NULL)
		{
			delete root;
			root = NULL;
		}
	}
	Node* getroot()
	{
		return root;
	}
	bool insert(int id, string url, string line)
	{
		return insert(id, url, line, root);
	}
	bool insert(int id, string url, string line, Node*& root)
	{
		if (!root)
		{
			root = new Node(id, url, line);
			return true;
		}
		if (strcmp(root->keyword.c_str(),line.c_str())==0)
		{
			int i = 0;
			string* temp = root->getURL();
			while(temp[i]!="")
			{
				if (temp[i] == url)
				{
					return false;
				}
				i++;
			}
			temp[i] = url;
			return true;
		}
		else if (strcmp(root->keyword.c_str(), line.c_str())<0)
		{
			return insert(id, url, line, root->right);
		}
		else if (strcmp(root->keyword.c_str(), line.c_str())>0)
		{
			return insert(id, url, line, root->left);
		}
	}
	bool search(string word)
	{
		return search(word, root);
	}
	bool search(string word, Node* root)
	{
		if (!root)
		{
			return false;
		}
		if (strcmp(root->keyword.c_str(), word.c_str()) > 0)
		{
			return search(word, root->left);
		}
		if (strcmp(root->keyword.c_str(),word.c_str())<0)
		{
			return search(word, root->right);
		}
		if (strcmp(root->keyword.c_str(), word.c_str())==0)
		{
			int i = 0;
			string* temp = root->getURL();
			while (temp[i] != "" &&i<53)
			{
				cout << root->URL[i] << endl;
				i++;
			}
			return true;
		}
	}
	void inOrder(Node* s) // private member function of AVL class
	{
		if (!s)
		{
			return;
		}
		inOrder(s->left);
		cout << s->ID << " " << s->URL << "\n" << s->keyword << endl;
		cout << "----------------------------------------------------\n";
		inOrder(s->right);
	}
	void inOrder()
	{
		inOrder(root);
	}
};
void readingfile(AVL &tree, ifstream& infile)
{
	string str1 = " ";
	int id = 0;
	string url = " ", keyword = " ";
	cout << "Enter filename\n";
	cin >> str1;
	bool val = false;
	string str = " ";
	int temp = 0, a = 0;
	infile.open(str1);
	int count = 0;
	if (str1 == "Assignment_data.txt")
	{
		while (infile >> id)
		{
			infile >> url;
			getline(infile, keyword);
			getline(infile, keyword);
			//Below is the code to tokenize each line and inserting each word
			//one by one
			a = 0;
			keyword[keyword.length()] = '\0';
			for (int p = 0; p<=keyword.length(); p++)
			{
				str = "";
				if (keyword[p] == ' '||keyword[p]=='\0')
				{
					temp = p;
					while(a<temp)
					{
						str+=keyword[a];
						if (a + 1 == temp)
						{	
					        tree.insert(id, url, str);							
						}
						a++;
					}
					a = temp + 1;
				}
			}
		}
	}
	else
	{
		cout << "Invalid Input\n";
	}
	infile.close();
}
int main()
{
	AVL tree;
	ifstream infile;
	readingfile(tree, infile);
	string keyword = " ";
	cout << "Enter a word to search\n";
	cin >> keyword;
	tree.search(keyword);
	return 0;
}