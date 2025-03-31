#include<iostream>
#include<conio.h>
#include<fstream>
#include<Windows.h>
#include<dos.h>
#include<cctype>
#include<string.h>
#include<sstream>
#include<stdlib.h>
#include<limits>

using namespace std;

const int ALPHABET_SIZE = 26;
const int MAX_NAME_LENGTH = 100;
const int PAGE_DATA_LIMIT = 10;
const int PAGE_LIMIT = 5;
const int DELAY_ITERATIONS = 100000000;
const int TABLE_SIZE = 200;

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

int MenuOption;
bool check = true;

int CurrentProductPage = 1;

void OpenMenu();
void CloseProgram();
void BackMenu();
void PageOptions();

class Productnode {
public:
    char ProductName[MAX_NAME_LENGTH];
    int ProductPrice;
    int ProductQuantity;
    int ExpiryDay, ExpiryMonth, ExpiryYear;
    bool consumable;

    Productnode* next;

    Productnode() : consumable(false), next(NULL) {}

    char* getProductName() {
        return ProductName;
    }

    void setProductName(string ProductName) {
        strncpy_s(this->ProductName, ProductName.c_str(), MAX_NAME_LENGTH - 1);
        this->ProductName[MAX_NAME_LENGTH - 1] = '\0';
    }

    Productnode(string Name, int Price, int Quantity, int Day, int Month, int Year, Productnode* nextValue) {
        setProductName(Name);
        ProductPrice = Price;
        ProductQuantity = Quantity;
        ExpiryDay = Day;
        ExpiryMonth = Month;
        ExpiryYear = Year;
        next = NULL;
        consumable = false;
    }
};

class Employeenode {
public:
    char EmmployeeAddress[MAX_NAME_LENGTH];
    char EmployeeName[MAX_NAME_LENGTH];
    int EmployeeNumber, EmployeeAge, EmployeePhone;

    Employeenode* next;

    void setName(string EmployeeName) {
        strncpy_s(this->EmployeeName, EmployeeName.c_str(), MAX_NAME_LENGTH - 1);
        this->EmployeeName[MAX_NAME_LENGTH - 1] = '\0';
    }

    void setAddress(string EmmployeeAddress) {
        strncpy_s(this->EmmployeeAddress, EmmployeeAddress.c_str(), MAX_NAME_LENGTH - 1);
        this->EmmployeeAddress[MAX_NAME_LENGTH - 1] = '\0';
    }

    char* getName() {
        return EmployeeName;
    }

    char* getAddress() {
        return EmmployeeAddress;
    }

    Employeenode() : next(NULL) {}

    Employeenode(string Name, string Address, int Number, int Age, int Phone, Employeenode* nextValue) {
        setName(Name);
        setAddress(Address);
        EmployeeNumber = Number;
        EmployeeAge = Age;
        EmployeePhone = Phone;
        next = NULL;
    }
};

class ProductPagesNode {
private:
    int CurrentData = 0;
    Productnode** ProductData;

public:
    int Num;
    ProductPagesNode* next;
    ProductPagesNode* prev;

    ProductPagesNode() {
        ProductData = new Productnode * [PAGE_DATA_LIMIT];
    }

    ProductPagesNode(int val) : Num(val), next(NULL), prev(NULL) {
        ProductData = new Productnode * [PAGE_DATA_LIMIT];
    }

    ~ProductPagesNode() {
        delete[] ProductData;
    }

    bool InsertData(Productnode* NewData) {
        if (CurrentData != PAGE_DATA_LIMIT) {
            ProductData[CurrentData] = NewData;
            CurrentData += 1;
            return true;
        }
        if (CurrentProductPage != PAGE_LIMIT) {
            return false;
        }
        cout << "Product Pages Full!";
        return false;
    }

    void Display() {
        system("cls");
        
        cout << "\nNAME\t\tPRICE\t\tQUANTITY\t\tEXPIRY DATE\n";
        for (int i = 0; i < CurrentData; i++) {
            cout << ProductData[i]->ProductName << "\t\t" 
                 << ProductData[i]->ProductPrice << "\t\t" 
                 << ProductData[i]->ProductQuantity << "\t\t\t" 
                 << ProductData[i]->ExpiryDay << "/" 
                 << ProductData[i]->ExpiryMonth << "/" 
                 << ProductData[i]->ExpiryYear << endl;
        }
        
        cout << "\nPage: " << CurrentProductPage;
        
        PageOptions();
    }
};

ProductPagesNode ProductPages[PAGE_LIMIT];

fstream EmpFile;
Employeenode NewEmployee;

fstream StockFile;
Productnode NewProduct;

fstream InvoiceFile;
Productnode InvoiceReport;

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void fordelay(int j) {
    for (int i = 0; i < j; i++) {
        // Delay loop
    }
}

void display(Productnode* temp){
	system("cls");
    cout << "\nNAME\t\tPRICE\t\tQUANTITY\t\tEXPIRY DATE\n";

    while (temp != NULL) {
        cout << temp->ProductName << "\t\t" 
             << temp->ProductPrice << "\t\t" 
             << temp->ProductQuantity << "\t\t\t";
		if(temp->consumable){
			cout << temp->ExpiryDay << "/" 
             	 << temp->ExpiryMonth << "/" 
             	 << temp->ExpiryYear << endl;
    	}
    	else{
    		cout << "NA\n";
		}
		temp = temp->next;
    }
	
	
}

void AscendingPrice(Productnode* head) {
    if (head == NULL) {
        cout << "No products to sort!\n";
        return;
    }

    Productnode* i, *j;
    int temp_data;
    char temp_name[MAX_NAME_LENGTH];
    int temp_quantity, temp_day, temp_month, temp_year;
    
    for (i = head; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->ProductPrice > j->ProductPrice) {
                // Swap data
                temp_data = j->ProductPrice;
                j->ProductPrice = i->ProductPrice;
                i->ProductPrice = temp_data;

                strcpy_s(temp_name, i->ProductName);
                strcpy_s(i->ProductName, j->ProductName);
                strcpy_s(j->ProductName, temp_name);

                temp_quantity = j->ProductQuantity;
                j->ProductQuantity = i->ProductQuantity;
                i->ProductQuantity = temp_quantity;

                temp_day = j->ExpiryDay;
                temp_month = j->ExpiryMonth;
                temp_year = j->ExpiryYear;
                
                j->ExpiryDay = i->ExpiryDay;
                j->ExpiryMonth = i->ExpiryMonth;
                j->ExpiryYear = i->ExpiryYear;
                
                i->ExpiryDay = temp_day;
                i->ExpiryMonth = temp_month;
                i->ExpiryYear = temp_year;
            }
        }
    }
    
    Productnode* temp = head;
    display(temp);
}

void DescendingPrice(Productnode* head) {
    if (head == NULL) {
        cout << "No products to sort!\n";
        return;
    }

    Productnode* i, *j;
    int temp_data;
    char temp_name[MAX_NAME_LENGTH];
    int temp_quantity, temp_day, temp_month, temp_year;
    
    for (i = head; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->ProductPrice < j->ProductPrice) {
                // Swap data
                temp_data = j->ProductPrice;
                j->ProductPrice = i->ProductPrice;
                i->ProductPrice = temp_data;

                strcpy_s(temp_name, i->ProductName);
                strcpy_s(i->ProductName, j->ProductName);
                strcpy_s(j->ProductName, temp_name);

                temp_quantity = j->ProductQuantity;
                j->ProductQuantity = i->ProductQuantity;
                i->ProductQuantity = temp_quantity;

                temp_day = j->ExpiryDay;
                temp_month = j->ExpiryMonth;
                temp_year = j->ExpiryYear;
                
                j->ExpiryDay = i->ExpiryDay;
                j->ExpiryMonth = i->ExpiryMonth;
                j->ExpiryYear = i->ExpiryYear;
                
                i->ExpiryDay = temp_day;
                i->ExpiryMonth = temp_month;
                i->ExpiryYear = temp_year;
            }
        }
    }

	
    Productnode* temp = head;
    display(temp);
}

void DefaultSort(Productnode* head) {
    Productnode* temp = head;
    display(temp);
}

void ViewProducts(Productnode* head) {
    if (head == NULL) {
        cout << "No products available!\n";
        BackMenu();
        return;
    }

    cout << "\n\n\t\t1.Sort Products by Price (Low to High)\n\t\t2.Sort Products by Price (High to Low)\n\t\t3.Default Sorting\n\nPlease Enter your choice: ";
    cin >> MenuOption;

    switch (MenuOption) {
        case 1: 
            AscendingPrice(head);
            break;
        case 2: 
            DescendingPrice(head);
            break;
        case 3: 
            DefaultSort(head);
            break;
        default:
            cout << "Invalid option!\n";
    }

    BackMenu();
}

void ViewEmployee(Employeenode* head) {
    if (head == NULL) {
        cout << "No employees to display!\n";
        BackMenu();
        return;
    }

    system("cls");
    cout << "\nEMPLOYEE NUMBER\t\tNAME\t\tAGE\t\tADDRESS\t\t\t\tPHONE\n";

    Employeenode* temp = head;
    while (temp != NULL) {
        cout << temp->EmployeeNumber << "\t\t\t" 
             << temp->EmployeeName << "\t\t" 
             << temp->EmployeeAge << "\t\t" 
             << temp->EmmployeeAddress << "\t\t\t\t" 
             << temp->EmployeePhone << endl;
        temp = temp->next;
    }

    BackMenu();
}

void AddProduct(Productnode*& head) {
    Productnode* NewProd = new Productnode;
    Productnode* temp = head;

    char PName[MAX_NAME_LENGTH];

    system("cls");
    cout << "\t\t\t ADD NEW STOCK RECORD  ";
    cout << "\n\nPlease Enter Product Name: ";
    cin >> PName;

    // Check for duplicate product names
    while (temp != NULL) {
        if ((strcmp(PName, temp->getProductName())) == 0) {
            cout << "This Product already exists! Please enter a new name!";
            Sleep(1000);
            delete NewProd;
            AddProduct(head);
            return;
        }
        temp = temp->next;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    NewProd->setProductName(PName);

    cout << "\nEnter Product Price: ";
    while (!(cin >> NewProd->ProductPrice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }

    cout << "\nEnter Product Quantity: ";
    while (!(cin >> NewProd->ProductQuantity)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }

	cout << "\nIs this product consumable? (1 for yes, 0 for no): ";
    while (!(cin >> NewProd->consumable) || (NewProd->consumable != 0 && NewProd->consumable != 1)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter 1 or 0: ";
    }

	if(NewProd->consumable){
	    cout << "\nEnter Product Expiry Day: ";
	    while (!(cin >> NewProd->ExpiryDay) || NewProd->ExpiryDay < 1 || NewProd->ExpiryDay > 31) {
	        cin.clear();
	        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        cout << "Invalid day. Please enter between 1-31: ";
	    }
	
	    cout << "\nEnter Product Expiry Month: ";
	    while (!(cin >> NewProd->ExpiryMonth) || NewProd->ExpiryMonth < 1 || NewProd->ExpiryMonth > 12) {
	        cin.clear();
	        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        cout << "Invalid month. Please enter between 1-12: ";
	    }
	
	    cout << "\nEnter Product Expiry Year: ";
	    while (!(cin >> NewProd->ExpiryYear) || NewProd->ExpiryYear < 2023) {
	        cin.clear();
	        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        cout << "Invalid year. Please enter 2023 or later: ";
	    }
	}
    // Add to linked list
    if (head == NULL) {
        head = NewProd;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = NewProd;
    }

    // Add to pages
    bool Success = ProductPages[CurrentProductPage].InsertData(NewProd);
    if (!Success && CurrentProductPage < PAGE_LIMIT) {
        CurrentProductPage += 1;
        ProductPages[CurrentProductPage].InsertData(NewProd);
    }

    cout << "\n\n****STOCK HAS BEEN ADDED SUCCESSFULLY****";
    BackMenu();
}

void AddEmployee(Employeenode*& head) {
    Employeenode* NewEmp = new Employeenode;
    Employeenode* temp = head;

    char EName[MAX_NAME_LENGTH];

    system("cls");
    cout << "\t\t\t REGISTER NEW EMPLOYEE ";
    cout << "\n\nPlease Enter the account Name of Employee: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(EName, MAX_NAME_LENGTH);

    // Check for duplicate employee names
    while (temp != NULL) {
        if ((strcmp(EName, temp->getName())) == 0) {
            cout << "This Employee already exists! Please enter a new employee name!";
            Sleep(1000);
            delete NewEmp;
            AddEmployee(head);
            return;
        }
        temp = temp->next;
    }

    NewEmp->setName(EName);

    cout << "\nEnter Employee Number: ";
    while (!(cin >> NewEmp->EmployeeNumber)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }

    cout << "\nEnter Employee Age: ";
    while (!(cin >> NewEmp->EmployeeAge) || NewEmp->EmployeeAge < 18 || NewEmp->EmployeeAge > 70) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid age. Please enter between 18-70: ";
    }

    cout << "\nEnter Employee Phone Number: ";
    while (!(cin >> NewEmp->EmployeePhone)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }

    string EAddress;
    cout << "\nEnter Employee Address: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, EAddress);
    NewEmp->setAddress(EAddress);

    // Add to linked list
    if (head == NULL) {
        head = NewEmp;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = NewEmp;
    }

    cout << "\n\n****EMPLOYEE HAS BEEN ADDED SUCCESSFULLY****";
    BackMenu();
}

void UpdateProduct(Productnode*& head) {
    if (head == NULL) {
        cout << "No products to update!\n";
        BackMenu();
        return;
    }

    Productnode* temp = head;
    bool Found = false;
    char PName[MAX_NAME_LENGTH];

    cout << "\nEnter the Product Name that you want to update: ";
    cin >> PName;

    while (temp != NULL && !Found) {
        if ((strcmp(PName, temp->getProductName()) == 0)) {
            system("cls");
            Found = true;

            string PItemName;
            cout << "\n\nEnter the New Name: ";
            cin >> PItemName;
            temp->setProductName(PItemName);

            cout << "\nEnter the New Price: ";
            while (!(cin >> temp->ProductPrice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number: ";
            }

            cout << "\nEnter the New Quantity: ";
            while (!(cin >> temp->ProductQuantity)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number: ";
            }

            cout << "\nEnter the New Expiry Day: ";
            while (!(cin >> temp->ExpiryDay) || temp->ExpiryDay < 1 || temp->ExpiryDay > 31) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid day. Please enter between 1-31: ";
            }

            cout << "\nEnter the New Expiry Month: ";
            while (!(cin >> temp->ExpiryMonth) || temp->ExpiryMonth < 1 || temp->ExpiryMonth > 12) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid month. Please enter between 1-12: ";
            }

            cout << "\nEnter the New Expiry Year: ";
            while (!(cin >> temp->ExpiryYear) || temp->ExpiryYear < 2023) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid year. Please enter 2023 or later: ";
            }

            cout << "\nIs this product non-consumable? (1 for yes, 0 for no): ";
            while (!(cin >> temp->consumable) || (temp->consumable != 0 && temp->consumable != 1)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter 1 or 0: ";
            }

            system("cls");
            cout << "\n\n\nChanges saved!";
        }
        temp = temp->next;
    }

    if (!Found) {
        system("cls");
        cout << "\nITEM RECORDS NOT FOUND!\a\a\a";
        Sleep(1000);
    }

    cout << "\n****RECORD UPDATED SUCCESSFULLY****";
    BackMenu();
}

void DeleteProduct(Productnode*& head) {
    if (head == NULL) {
        cout << "No products to delete!\n";
        BackMenu();
        return;
    }

    char name[MAX_NAME_LENGTH];
    cout << "Enter a Product name to delete: \n";
    cin >> name;

    Productnode *temp = NULL;
    Productnode *prevptr = head;
    Productnode *currentptr = head->next;

    if (strcmp(head->getProductName(), name) == 0) {
        temp = head;
        head = head->next;
        delete temp;
        cout << "Product has been deleted successfully!";
    } else {
        while (currentptr != NULL) {
            if ((strcmp(name, currentptr->getProductName())) == 0) {
                cout << "Product has been deleted successfully!";
                temp = currentptr;
                prevptr->next = currentptr->next;
                delete temp;
                break;
            }
            prevptr = prevptr->next;
            currentptr = currentptr->next;
        }
        
        if (currentptr == NULL) {
            cout << "Product not found!";
        }
    }

    cout << "\n****PRODUCT RECORD DELETED SUCCESSFULLY****";
    BackMenu();
}

void DeleteEmployee(Employeenode* &head) {
    if (head == NULL) {
        cout << "No employees to delete!\n";
        BackMenu();
        return;
    }

    char name[MAX_NAME_LENGTH];
    cout << "Enter an Employee name to delete: \n";
    cin >> name;

    Employeenode *temp = NULL;
    Employeenode *prevptr = head;
    Employeenode *currentptr = head->next;

    if (strcmp(head->getName(), name) == 0) {
        temp = head;
        head = head->next;
        delete temp;
        cout << "Employee has been deleted successfully!";
    } else {
        while (currentptr != NULL) {
            if ((strcmp(name, currentptr->getName())) == 0) {
                cout << "Employee has been deleted successfully!";
                temp = currentptr;
                prevptr->next = currentptr->next;
                delete temp;
                break;
            }
            prevptr = prevptr->next;
            currentptr = currentptr->next;
        }
        
        if (currentptr == NULL) {
            cout << "Employee not found!";
        }
    }

    cout << "\n****EMPLOYEE RECORD DELETED SUCCESSFULLY****";
    BackMenu();
}

struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isWordEnd;
};

struct TrieNode* getNode() {
    struct TrieNode* pNode = new TrieNode;
    pNode->isWordEnd = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

void insert(struct TrieNode* root, const string key) {
    struct TrieNode* pCrawl = root;

    for (int level = 0; level < key.length(); level++) {
        int index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }
    pCrawl->isWordEnd = true;
}

bool isLastNode(struct TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

void suggestionsRec(struct TrieNode* root, string currPrefix) {
    if (root->isWordEnd)
        cout << currPrefix << endl;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            char child = 'a' + i;
            suggestionsRec(root->children[i], currPrefix + child);
        }
    }
}

void SearchProduct(Productnode*& head, TrieNode* root) {
    system("cls");

    if (head == NULL) {
        cout << "No Products Exist";
        BackMenu();
        return;
    }

    Productnode* temp = head;
    bool Found = false;
    char PName[MAX_NAME_LENGTH];

    cout << "\nEnter the Product Name to search: ";
    cin >> PName;

    while (temp != NULL && !Found) {
        if ((strcmp(PName, temp->getProductName()) == 0)) {
            Found = true;
            break;
        }
        temp = temp->next;
    }

    if (!Found) {
        cout << "RECORD NOT FOUND!";
    } else {
        cout << "\nProduct Name: " << temp->ProductName;
        cout << "\nProduct Price: " << temp->ProductPrice;
        cout << "\nProduct Quantity: " << temp->ProductQuantity;
        cout << "\nProduct Expiry Date: " << temp->ExpiryDay << "/" 
             << temp->ExpiryMonth << "/" << temp->ExpiryYear;
        cout << "\nNon-consumable: " << (temp->consumable ? "Yes" : "No");
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    BackMenu();
}

void SearchEmployee(Employeenode*& head) {
    if (head == NULL) {
        cout << "No employees to search!\n";
        BackMenu();
        return;
    }

    Employeenode* current = head;
    int Employee_Num;

    cout << "\n\nEnter Employee Number To Search: ";
    while (!(cin >> Employee_Num)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }

    while (current != NULL) {
        if (current->EmployeeNumber == Employee_Num) {
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        cout << "RECORD NOT FOUND!";
    } else {
        cout << "\nEmployee Number: " << current->EmployeeNumber;
        cout << "\nEmployee Name: " << current->EmployeeName;
        cout << "\nEmployee Age: " << current->EmployeeAge;
        cout << "\nEmployee Address: " << current->EmmployeeAddress;
        cout << "\nEmployee Phone Number: " << current->EmployeePhone;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    BackMenu();
}

void LoadData(Productnode*& head, Employeenode*& Ehead) {
    StockFile.open("StockRecord.txt", ios::in);
    if (!StockFile.is_open()) {
        cerr << "Error opening stock file!\n";
        return;
    }

    while (StockFile.read((char*)&NewProduct, sizeof(NewProduct))) {
        Productnode* NewProd = new Productnode(
            NewProduct.getProductName(), 
            NewProduct.ProductPrice, 
            NewProduct.ProductQuantity, 
            NewProduct.ExpiryDay, 
            NewProduct.ExpiryMonth, 
            NewProduct.ExpiryYear, 
            NewProduct.next
        );
        NewProd->consumable = NewProduct.consumable;

        if (head == NULL) {
            head = NewProd;
        } else {
            Productnode* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = NewProd;
        }
        
        bool Success = ProductPages[CurrentProductPage].InsertData(NewProd);
        if (!Success && CurrentProductPage < PAGE_LIMIT) {
            CurrentProductPage += 1;
            ProductPages[CurrentProductPage].InsertData(NewProd);
        }
    }
    StockFile.close();

    EmpFile.open("EmployeeRecord.txt", ios::in);
    if (!EmpFile.is_open()) {
        cerr << "Error opening employee file!\n";
        return;
    }

    Employeenode* Etemp = Ehead;
    while (EmpFile.read((char*)&NewEmployee, sizeof(NewEmployee))) {
        Employeenode* NewEmp = new Employeenode(
            NewEmployee.getName(), 
            NewEmployee.getAddress(), 
            NewEmployee.EmployeeNumber, 
            NewEmployee.EmployeeAge, 
            NewEmployee.EmployeePhone, 
            NewEmployee.next
        );

        if (Ehead == NULL) {
            Ehead = NewEmp;
        } else {
            Etemp = Ehead;
            while (Etemp->next != NULL) {
                Etemp = Etemp->next;
            }
            Etemp->next = NewEmp;
        }
    }
    EmpFile.close();
}

void SaveData(Productnode* head, Employeenode* Ehead) {
    StockFile.open("StockRecord.txt", ios::out);
    if (!StockFile.is_open()) {
        cerr << "Error opening stock file for writing!\n";
        return;
    }

    Productnode* temp = head;
    while (temp != NULL) {
        NewProduct.setProductName(temp->ProductName);
        NewProduct.ProductPrice = temp->ProductPrice;
        NewProduct.ProductQuantity = temp->ProductQuantity;
        NewProduct.ExpiryDay = temp->ExpiryDay;
        NewProduct.ExpiryMonth = temp->ExpiryMonth;
        NewProduct.ExpiryYear = temp->ExpiryYear;
        NewProduct.consumable = temp->consumable;
        NewProduct.next = temp->next;
        StockFile.write((char*)&NewProduct, sizeof(Productnode));
        temp = temp->next;
    }
    StockFile.close();

    EmpFile.open("EmployeeRecord.txt", ios::out);
    if (!EmpFile.is_open()) {
        cerr << "Error opening employee file for writing!\n";
        return;
    }

    Employeenode* Etemp = Ehead;
    while (Etemp != NULL) {
        NewEmployee.setName(Etemp->EmployeeName);
        NewEmployee.setAddress(Etemp->EmmployeeAddress);
        NewEmployee.EmployeeNumber = Etemp->EmployeeNumber;
        NewEmployee.EmployeeAge = Etemp->EmployeeAge;
        NewEmployee.EmployeePhone = Etemp->EmployeePhone;
        NewEmployee.next = Etemp->next;
        EmpFile.write((char*)&NewEmployee, sizeof(Employeenode));
        Etemp = Etemp->next;
    }
    EmpFile.close();
}

void Transaction(Productnode* &head) {
    if (head == NULL) {
        cout << "No products available for transaction!\n";
        BackMenu();
        return;
    }

    float TotalPrice = 0;
    char ItemName[MAX_NAME_LENGTH] = "";
    bool Found = false;
    
    cout << "\nGENERATE TRANSACTION";
    cout << "\nEnter 'End' To Generate Invoice!";
    
    remove("InvoiceFile.txt");
    
    while (true) {
        StockFile.open("StockRecord.txt", ios::in | ios::out);
        if (!StockFile.is_open()) {
            cerr << "Failed to open stock file!";
            return;
        }

        InvoiceFile.open("InvoiceFile.txt", ios::out | ios::app);
        if (!InvoiceFile.is_open()) {
            cerr << "Failed to open invoice file!";
            StockFile.close();
            return;
        }
        
        cout << "\nName of item (or 'End' to finish): ";
        cin >> ItemName;
        
        if (strcmp(ItemName, "End") == 0) {
            break;
        }
        
        int Day, Month, Year;
        cout << "\n\t\t\tDATE OF TRANSACTION";
        cout << "\nEnter Today Day: ";
        while (!(cin >> Day) || Day < 1 || Day > 31) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid day. Please enter between 1-31: ";
        }

        cout << "Enter Today Month: ";
        while (!(cin >> Month) || Month < 1 || Month > 12) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid month. Please enter between 1-12: ";
        }

        cout << "Enter Today Year: ";
        while (!(cin >> Year) || Year < 2023) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid year. Please enter 2023 or later: ";
        }

        bool itemFound = false;
        while (StockFile.read((char*)&NewProduct, sizeof(NewProduct))) {
            if ((strcmp(ItemName, NewProduct.getProductName())) == 0) {
                itemFound = true;
                int Quantity;
                cout << "Enter Quantity of the Item: ";
                while (!(cin >> Quantity) || Quantity <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid quantity. Please enter a positive number: ";
                }

                if (Quantity > NewProduct.ProductQuantity) {
                    cout << "Not enough stock available! Available: " << NewProduct.ProductQuantity << "\n";
                    int ch;
                    cout << "Press 1 to go to Menu or any other key to continue: ";
                    cin >> ch;
                    if (ch == 1) {
                        StockFile.close();
                        InvoiceFile.close();
                        BackMenu();
                        return;
                    }
                    continue;
                }

                int SetQuantity = NewProduct.ProductQuantity - Quantity;
                
                // Update in-memory list
                Productnode* temp = head;
                while (temp != NULL) {
                    if ((strcmp(ItemName, temp->getProductName()) == 0)) {
                        temp->ProductQuantity = SetQuantity;
                        break;
                    }
                    temp = temp->next;
                }
                
                // Update in file
                NewProduct.ProductQuantity = SetQuantity;
                TotalPrice += NewProduct.ProductPrice * Quantity;
                
                InvoiceReport.setProductName(NewProduct.getProductName());
                InvoiceReport.ProductPrice = NewProduct.ProductPrice;
                InvoiceReport.ProductQuantity = Quantity;
                InvoiceReport.ExpiryDay = NewProduct.ExpiryDay;
                InvoiceReport.ExpiryMonth = NewProduct.ExpiryMonth;
                InvoiceReport.ExpiryYear = NewProduct.ExpiryYear;
                InvoiceReport.consumable = NewProduct.consumable;
                
                int Position = -1 * static_cast<int>(sizeof(NewProduct));
                StockFile.seekp(Position, ios::cur);
                StockFile.write((char*)&NewProduct, sizeof(Productnode));
                
                InvoiceFile.write((char*)&InvoiceReport, sizeof(Productnode));
                Found = true;
                break;
            }
        }

        if (!itemFound) {
            cout << "Item doesn't exist in the Database!\n";
        }

        InvoiceFile.close();
        StockFile.close();
    }

    if (!Found) {
        system("cls");
        cout << "\nNO ITEMS WERE PURCHASED!\a\a\a";
        Sleep(1000);
        BackMenu();
        return;
    }
    
    // Display invoice
    system("cls");
    cout << "\n\n\t\t\t CUSTOMER INVOICE";
    cout << "\n\nNAME\t\tPRICE\t\tQUANTITY\t\tEXPIRY DATE\n";

    InvoiceFile.open("InvoiceFile.txt", ios::in);
    if (!InvoiceFile.is_open()) {
        cerr << "Failed to open invoice file for reading!";
        BackMenu();
        return;
    }

    while (InvoiceFile.read((char*)&InvoiceReport, sizeof(Productnode))) {
        cout << InvoiceReport.getProductName() << "\t\t" 
             << InvoiceReport.ProductPrice << "\t\t" 
             << InvoiceReport.ProductQuantity << "\t\t\t" 
             << InvoiceReport.ExpiryDay << "/" 
             << InvoiceReport.ExpiryMonth << "/" 
             << InvoiceReport.ExpiryYear << endl;
    }
    InvoiceFile.close();

    cout << "\n\n\t\tTotal Price: " << TotalPrice;
    BackMenu();
}

void DisplayNode(Productnode* head) {
    if (head == NULL) {
        cout << "List is empty!\n";
        return;
    }

    cout << "NULL <--> ";
    Productnode* temp = head;
    while (temp != NULL) {
    	cout << temp->ProductName << " --> ";
    	        temp = temp->next;
    }
    cout << "NULL" << endl;
}

void CloseProgram() {
    printf("\n\n\n\nLogged Off!");
}

class HashTableEntry {
public:
    int k;
    int v;
    HashTableEntry(int k, int v) : k(k), v(v) {}
};

class HashMapTable {
private:
    HashTableEntry** t;
public:
    HashMapTable() {
        t = new HashTableEntry * [TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            t[i] = NULL;
        }
    }

    ~HashMapTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (t[i] != NULL)
                delete t[i];
        }
        delete[] t;
    }

    int HashFunc(int k) {
        return k % TABLE_SIZE;
    }

    void Insert(int k, int v) {
        int h = HashFunc(k);
        while (t[h] != NULL && t[h]->k != k) {
            h = HashFunc(h + 1);
        }
        if (t[h] != NULL)
            delete t[h];
        t[h] = new HashTableEntry(k, v);
    }

    int SearchKey(int k) {
        int h = HashFunc(k);
        while (t[h] != NULL && t[h]->k != k) {
            h = HashFunc(h + 1);
        }
        if (t[h] == NULL)
            return -1;
        else
            return t[h]->v;
    }
};

Productnode* Phead = NULL;
Employeenode* Ehead = NULL;

void BackMenu() {
    int option;
    do {
        cout << "\n\n1: Main Menu \n0: Exit \n";
        cin >> option;

        system("cls");

        if (option == 1) {
            OpenMenu();
            return;
        }
        else if (option == 0) {
            SaveData(Phead, Ehead);
            CloseProgram();
            exit(0);
        }
        else {
            cout << "\nInvalid Option!\a";
        }
    } while (true);
}

void PageOptions() {
    int option;
    do {
        cout << "\n\n1: Next Page \n2: Previous Page \n0: Return To Menu \n";
        cin >> option;

        system("cls");

        if (option == 1) {
            if (CurrentProductPage == PAGE_LIMIT) {
                cout << "\nThis is the Last page, you can't go further.";
                continue;
            }
            CurrentProductPage += 1;
            ProductPages[CurrentProductPage].Display();
            return;
        }
        else if (option == 2) {
            if (CurrentProductPage == 1) {
                cout << "\nThis is the first page, you can't go back.";
                continue;
            }
            CurrentProductPage -= 1;
            ProductPages[CurrentProductPage].Display();
            return;
        }
        else if (option == 0) {
            OpenMenu();
            return;
        }
        else {
            cout << "\nInvalid Option!\a";
        }
    } while (true);
}

void OpenMenu() {
    system("cls");
    system("color 2");

    cout << "\n\n\t\t\t\t CHILL MARKET MANAGEMENT";
    cout << "\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    cout << "\n\n\t\t1.Add Product\n\t\t2.Add Employee\n\t\t3.View Products\n\t\t4.View Employees\n\t\t5.Update A Product\n\t\t6.Delete A Product\n\t\t7.Delete A Employee\n\t\t8.Transaction\n\t\t9.Search Product\n\t\t10.Search Employee\n\t\t11.Exit Program\n\nPlease Enter your choice: ";

    cin >> MenuOption;

    system("cls");

    struct TrieNode* root = getNode();

    switch (MenuOption) {
        case 1: 
            AddProduct(Phead);
            break;
        case 2: 
            AddEmployee(Ehead);
            break;
        case 3: 
            ViewProducts(Phead);
            break;
        case 4: 
            ViewEmployee(Ehead);
            break;
        case 5: 
            UpdateProduct(Phead);
            break;
        case 6: 
            DeleteProduct(Phead);
            break;
        case 7: 
            DeleteEmployee(Ehead);
            break;
        case 8: 
            Transaction(Phead);
            break;
        case 9: 
            SearchProduct(Phead, root);
            break;
        case 10: 
            SearchEmployee(Ehead);
            break;
        case 11:
            SaveData(Phead, Ehead);
            CloseProgram();
            exit(0);
        default:
            cout << "Invalid option! Please try again.\n";
            Sleep(1000);
            OpenMenu();
    }
}

int main() {
    HideCursor();
    system("Color 9");

    HashMapTable hash;
    hash.Insert(12, 12); // Password = 12

    cout << "\n\n\t\t\t******* CHILL MARKET *******";
    cout << "\n\n\t\t\t----------------------------";
    cout << "\n\n\t\t\tEnter the Password to login: ";
    
    int GetPass;
    cin >> GetPass;
    cout << "\n\n\t\t\t----------------------------";

    if (hash.SearchKey(GetPass) == 12) {
        cout << "\n\n\n\t\t\t   ^^^Password Match!^^^\n\n\n\t\t\tLOADING";

        LoadData(Phead, Ehead);

        for (int i = 0; i <= 6; i++) {
            fordelay(DELAY_ITERATIONS);
            printf(".");
        }

        system("cls");
        OpenMenu();
    }
    else {
        cout << "\n\n\t\t\t**Error: Invalid Password!**\a\a\a";
        Sleep(2000);
    }
    
    return 0;
}