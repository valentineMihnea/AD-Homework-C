// stdio.h for the printf function
#include <stdio.h>
// stdlib.h and time.h for generating random numbers
#include <stdlib.h>
#include <time.h>

// The function that divides the books among the employees.
void divideBooks(int *books, int numBooks, int numEmployees) {
    // We find out how many pages there are 
    int totalPages = 0;
    int currentEmployee = 1;
    for (int i =0;i<numBooks;i++){
        totalPages += books[i];
    }
    // We find what the ideal pages one employee should read, as the number of pages divided by the number of employees.
    int idealPages = totalPages / numEmployees;
    // Create a variable that will track how many pages one employee has already read
    int readPages = 0;
    // Reiterate through every single book.
    for(int i=0;i<numBooks;i++){
        // Add the current book's pages to the employee's reading number.
        readPages += books[i];
        // Print the current book's pages.
        printf("%d ", books[i]);
        if(i < numBooks -1){
            // Calculate how many pages our employee would read if he was to read the next book's pages.
            int toBeReadPages = readPages + books[i+1];
            // If he would read more pages than our ideal number of pages.
            if(toBeReadPages > idealPages){
                // Calculate the difference between the pages we already read and the ideal number of pages.
                int readIdealDiff = idealPages - readPages;
                // Calculate the difference between the pages we already read + the next book's pages and the ideal number of pages.
                int toBeReadIdealDiff = toBeReadPages - idealPages;
                // If reading the next book would put us closer to our ideal number of pages we read it.
                if(toBeReadIdealDiff < readIdealDiff){
                    continue;
                } 
                // If not, we print a "- " and reset the readPages to 0, meaning we go to the next employee, but not if we are on the last employee already
                else{
                    if(currentEmployee < numEmployees){
                        printf("- ");
                        readPages=0;
                        currentEmployee++;
                    }
                }
            }
        }
    }
}

// Create a random number of books.
int randomizeBooks(int minNumber,int maxNumber){
    time_t t; 
    srand((unsigned)time(&t));
    return (rand() % (maxNumber - minNumber + 1)) + minNumber;
}

// Create a number random of pages
void randomizePages(int *books, int numBooks, int minNumber,int maxNumber ) {
    time_t t;
    srand((unsigned)time(&t));
    for(int i = 0; i < numBooks;i++){
        books[i] = (rand() % (maxNumber - minNumber + 1)) + minNumber;
    }
}

int main() {
    // The number of employees we divide the books among.
    int numEmployees = 3;
    // Set to 0 for a pre-determined amount of books and pages, set to 1 for random amount of books and pages.
    int randomInput = 1;
    // The minimum and maximum numbers for the amount of books and pages.
    int minRandomBooks = 3;
    int maxRandomBooks = 21;
    int minRandomPages = 1;
    int maxRandomPages = 1000;

    // If we want a random amount of books and pages 
    if(randomInput==1){
        // We randomize the amount of books, based on our minimum and maximum values set above.
        int numBooks = randomizeBooks(minRandomBooks,maxRandomBooks);
        // We make space in memory for the books, based on the amount of books we have.
        int* books = malloc(numBooks * sizeof(int)); 
        // We randomize each book's pages, based on the minimum and maximum values set above.
        randomizePages(books, numBooks, minRandomPages,maxRandomPages);
        // We divide the books among the employees.
        divideBooks(books, numBooks, numEmployees);
        // After we are done, we free the books from memory.
        free(books);
    }
    // If a pre-determined amount of books is desired.
    else{
        // We set each book's pages. 
        int books[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};
        // We find out how many books there are in total.
        int numBooks = sizeof(books) / sizeof(books[0]);
        // We divide the books among the employees.
        divideBooks(books, numBooks, numEmployees);
    }
    return 0;
}