#include <iostream>
#include <string>
using namespace std;
const int MAX_BOOKS = 100;
const int MAX_MEMBERS = 50;
const int MAX_STAFF = 10;
const int MAX_BORROWED_BOOKS = 10;

class Person {
protected:
     string Name;
     string Id;

public:
    Person() : Name(""), Id("") {} 
    Person(const  string& name, const  string& id) : Name(name), Id(id) {}
    virtual void login() = 0;
    virtual void logout() = 0;
    virtual ~Person() = default;
};

class Book {
private:
     string Title;
     string Author;
     string ISBN;
    bool isAvailable;

public:
    
    Book() : Title(""), Author(""), ISBN(""), isAvailable(true) {}

    
    Book(const  string& title, const  string& author, const  string& ISBN)
        : Title(title), Author(author), ISBN(ISBN), isAvailable(true) {}

    bool borrowBook() {
        if (isAvailable) {
            isAvailable = false;
            return true;
        }
        return false;
    }

    void returnBook() {
        isAvailable = true;
    }

    string getTitle() const { return Title; }
     string getAuthor() const { return Author; }
     string getISBN() const { return ISBN; }
    bool availability() const { return isAvailable; }
};

class Member : public Person {
private:
    Book* borrowedBooks[MAX_BORROWED_BOOKS];
    int BorrowedCount;

public:
    
    Member() : Person(), BorrowedCount(0) {
        for (int i = 0; i < MAX_BORROWED_BOOKS; ++i) {
            borrowedBooks[i] = nullptr;
        }
    }

    
    Member(const  string& name, const  string& id) : Person(name, id), BorrowedCount(0) {
        for (int i = 0; i < MAX_BORROWED_BOOKS; ++i) {
            borrowedBooks[i] = nullptr;
        }
    }

    void login() override {
         cout << "Member " << Name << " logged in." <<  endl;
    }

    void logout() override {
         cout << "Member " << Name << " logged out." <<  endl;
    }

    void borrowBook(Book& book) {
        if (BorrowedCount < MAX_BORROWED_BOOKS && book.borrowBook()) {
            borrowedBooks[BorrowedCount++] = &book;
             cout << "Book borrowed: " << book.getTitle() <<  endl;
        }
        else {
             cout << "Cannot borrow book: " << book.getTitle() <<  endl;
        }
    }

    void returnBook(Book& book) {
        for (int i = 0; i < BorrowedCount; ++i) {
            if (borrowedBooks[i] == &book) {
                book.returnBook();
                borrowedBooks[i] = borrowedBooks[--BorrowedCount];
                borrowedBooks[BorrowedCount] = nullptr;
                 cout << "Book returned: " << book.getTitle() <<  endl;
                return;
            }
        }
         cout << "Book not found in borrowed list: " << book.getTitle() <<  endl;
    }
};

class Staff : public Person {
public:
    
    Staff() : Person() {}

    
    Staff(const  string& name, const  string& id) : Person(name, id) {}

    void login()  {
         cout << "Staff " << Name << " logged in." <<  endl;
    }

    void logout()  {
         cout << "Staff " << Name << " logged out." <<  endl;
    }

    void addBook(Book books[], int& bookCount, const Book& book) {
        if (bookCount < MAX_BOOKS) {
            books[bookCount++] = book;
             cout << "Book added: " << book.getTitle() <<  endl;
        }
        else {
             cout << "Book array is full. Cannot add book: " << book.getTitle() <<  endl;
        }
    }

    void removeBook(Book books[], int& bookCount, const  string& ISBN) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getISBN() == ISBN) {
                 cout << "Book removed: " << books[i].getTitle() <<  endl;
                books[i] = books[--bookCount];
                return;
            }
        }
         cout << "Book not found: " << ISBN <<  endl;
    }
};

class Library {
private:
    Book books[MAX_BOOKS];
    Member members[MAX_MEMBERS];
    Staff staffs[MAX_STAFF];
    int BookCount;
    int MemberCount;
    int StaffCount;

public:
    Library() : BookCount(0), MemberCount(0), StaffCount(0) {}

    void addBook(const Book& book) {
        if (BookCount < MAX_BOOKS) {
            books[BookCount++] = book;
        }
    }

    void addMember(const Member& member) {
        if (MemberCount < MAX_MEMBERS) {
            members[MemberCount++] = member;
        }
    }

    void addStaff(const Staff& staff) {
        if (StaffCount < MAX_STAFF) {
            staffs[StaffCount++] = staff;
        }
    }

    Book* getBooks() {
        return books;
    }

    Member* getMembers() {
        return members;
    }

    Staff* getStaffs() {
        return staffs;
    }

    int& getBookCount() {
        return BookCount;
    }

    int getMemberCount() const {
        return MemberCount;
    }

    int getStaffCount() const {
        return StaffCount;
    }
};

int main() {
    Library library;

    Member m1("John Doe", "M001");
    Staff s1("Jane Smith", "S001");

    library.addMember(m1);
    library.addStaff(s1);

    Book b1("C++ Programming", "Bjarne Stroustrup", "12345");
    Book b2("Effective C++", "Scott Meyers", "67890");

    library.addBook(b1);
    library.addBook(b2);

    s1.login();
    Book newBook("Design Patterns", "Erich Gamma", "11223");
    s1.addBook(library.getBooks(), library.getBookCount(), newBook);
    s1.logout();

    m1.login();
    m1.borrowBook(b1);
    m1.borrowBook(b2);
    m1.returnBook(b1);
    m1.logout();

    return 0;
}
