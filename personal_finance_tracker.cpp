#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <limits>
#include <regex>

using namespace std;

// Structure to store transaction details
struct Transaction {
string type; // "Income" or "Expense"
string category;
double amount;
string date; // Date of the transaction
};

// Class to handle personal finance tracking
class FinanceTracker {
private:
vector<Transaction> transactions; // Vector to store all transactions
double totalIncome;  // Total income added
double totalSpent;   // Total expense added

public:
// Constructor to initialize income and expense
FinanceTracker() {
totalIncome = 0;
totalSpent = 0;
}

// Function to add income
void addIncome(double amount, string date) {
totalIncome += amount;
Transaction incomeTransaction = {"Income", "N/A", amount, date};
transactions.push_back(incomeTransaction);
cout << "Income added: Rs." << amount << " on " << date << endl;
}

// Function to add an expense
void addExpense(string category, double amount, string date) {
totalSpent += amount;
Transaction expenseTransaction = {"Expense", category, amount, date};
transactions.push_back(expenseTransaction);
cout << "Expense added: " << category << " - Rs." << amount << " on " << date << endl;
}

// Function to display spending insights (total expenses per category)
void displaySpendingInsights() {
unordered_map<string, double> categorySpending;

// Calculate total spending per category  
for (const auto& transaction : transactions) {  
    if (transaction.type == "Expense") {  
        categorySpending[transaction.category] += transaction.amount;  
    }  
}  

cout << "\n--- Spending Insights ---\n";  
for (const auto& entry : categorySpending) {  
    cout << "Category: " << entry.first << ", Total Spent: Rs." << entry.second << endl;  
}
}

// Function to display monthly summary
void displayMonthlySummary() {
cout << "\n--- Monthly Summary ---\n";
cout << "Total Income: Rs." << totalIncome << endl;
cout << "Total Expenses: Rs." << totalSpent << endl;
cout << "Balance (Income - Expenses): Rs." << (totalIncome - totalSpent) << endl;
}

// Function to display current balance
void displayCurrentBalance() {
cout << "\n--- Current Balance ---\n";
cout << "Current Balance: Rs." << (totalIncome - totalSpent) << endl;
}

// Function to display all transactions with date
void displayTransactions() {
cout << "\n--- All Transactions ---\n";
for (const auto& transaction : transactions) {
cout << "Type: " << transaction.type << ", Category: " << transaction.category
<< ", Amount: Rs." << transaction.amount << ", Date: " << transaction.date << endl;
}
}
};

bool isValidAmount(double amount) {
return amount >= 0;
}

bool isValidDate(const string& date) {
regex datePattern(R"(\d{4}-\d{2}-\d{2})");
return regex_match(date, datePattern);
}

int main() {
FinanceTracker tracker;

while (true) {
cout << "\n1. Add Income\n2. Add Expense\n3. Display Spending Insights\n4. Display Monthly Summary\n5. Display Current Balance\n6. Display All Transactions\n7. Exit\n";
int choice;
cout << "Enter your choice: ";
while (!(cin >> choice)) {
    cout << "Invalid choice. Please enter a number: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

if (choice == 1) {  
    double amount;  
    string date;  
    cout << "Enter income amount: Rs.";  
    while (!(cin >> amount) || !isValidAmount(amount)) {
        cout << "Invalid amount. Enter a valid positive number: Rs.";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }  
    cout << "Enter the date of income (YYYY-MM-DD): ";  
    cin >> date;  
    while (!isValidDate(date)) {
        cout << "Invalid date format. Please enter date in YYYY-MM-DD: ";
        cin >> date;
    }  
    tracker.addIncome(amount, date);  
}  
else if (choice == 2) {  
    string category;  
    double amount;  
    string date;  
    cout << "Enter expense category: ";  
    cin >> ws;  
    getline(cin, category);  
    cout << "Enter expense amount: Rs.";  
    while (!(cin >> amount) || !isValidAmount(amount)) {
        cout << "Invalid amount. Enter a valid positive number: Rs.";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }  
    cout << "Enter the date of expense (YYYY-MM-DD): ";  
    cin >> date;  
    while (!isValidDate(date)) {
        cout << "Invalid date format. Please enter date in YYYY-MM-DD: ";
        cin >> date;
    }  
    tracker.addExpense(category, amount, date);  
}  
else if (choice == 3) {  
    tracker.displaySpendingInsights();  
}  
else if (choice == 4) {  
    tracker.displayMonthlySummary();  
}  
else if (choice == 5) {  
    tracker.displayCurrentBalance();  
}  
else if (choice == 6) {  
    tracker.displayTransactions();  
}  
else if (choice == 7) {  
    cout << "Exiting... Goodbye!" << endl;  
    break;  
}  
else {  
    cout << "Invalid choice. Please try again." << endl;  
}
}

return 0;
}