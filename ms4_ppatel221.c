#include <stdio.h>
#define MAX_INVENTORY_SIZE 10
#define TAX .13
#define MAX_ITEMS 10


struct Cart
{
    int sku[MAX_ITEMS];
    float price[MAX_ITEMS];
    int quantity[MAX_ITEMS];
    float totalCost;
    int size;
};


/*clears screen*/
void clear();

/*Calls menu and displays options for the user*/
void menu();


/*Takes value from the user and validates to see if it is in the range specified and  when it is it returns the number to the main function*/
int validate();

/*Displays the SKU numbers alot with the price for each item*/
void displayInventory(const int sku[],const float price[]);

/*Searches the inventory for the SKU number provided by the user*/
int searchInventory(const int sku[],const int item);

/*checks the price of the SKU number returned from searchInventory function*/
void checkPrice(const int sku[],const float price[]);

/*Displays what the user has added the to cart*/
void displayCart(const struct Cart* pShoppingCart);

/*Promts the user to enter the SKU number and the quantity of the item and adds it to the cart*/
void addCart(struct Cart* pShoppingCart,const int sku[],const float price[]);

/*Removes all the items from the cart*/
void removeCart(struct Cart* pShoppingCart);

/*Calculates total cost by multiplying Price by the amount of quantity of each it has*/
void checkout( struct Cart* pShoppingCart);

/*Reads a file and separates the integers and floats and stores them in a respective arrays*/
int readInventory(const char filename[],int sku[],float price[]);

/*Prints what is in the shopping cart and the total price of your items to a file*/
void printReceipt(const char filename[], struct Cart* pShoppingCart);



int main()
{

    /*Variable declaration for the user input selection option*/
    int input= 0;
    


    /*Declares a struct named myCart and assigns 0 to it and its size to 0 as well*/
    struct Cart myCart= {0} ;
    myCart.size = 0;

    /*Initializes arrays for SKU and price to be MAX_INVENTORY_SIZE which is 10*/
    int skuList[MAX_INVENTORY_SIZE] = {0} ;
    float priceList[MAX_INVENTORY_SIZE] = {0};
            
    /*reads return from the readInventory function to check if the file opens or not*/
    int readNum = 0;
            
    /*readInventory reads the file "Inventory.dat" and stores the sku and price values to the respective arrays*/
    readNum = readInventory("inventory.dat" ,skuList, priceList);
 
    /*If value returned by the readInventory reads -1 which means its a failur. It will print an error message and
    if it reads sucesfully it will excute the rest of the interactive program*/            
    if(readNum == -1)
    {
        printf("Failed to open the file!\n");
    }
    else
    {
        clear();
        printf("Welcome to the groccery store!\n");
        printf("==============================\n");

        /*keeps looping until user enters 8*/
        do{

                menu();
                printf("Select: ");


                /*calls validate function and sets low value to 1 and high value to 8*/
                input = validate(1,8);

                if(input == 1)
                {
                    displayInventory(skuList ,priceList);

                }
                else if(input == 2)
                {
                    checkPrice(skuList, priceList);

                }
                else if(input == 3)
                {
                    displayCart(&myCart);

                }
                else if(input == 4)
                {
                    addCart(&myCart , skuList , priceList);

                }
                else if(input == 5)
                {
                    removeCart(&myCart);

                }
                else if(input == 6)
                {
                    checkout(&myCart);
                    printReceipt("receipt.dat",&myCart);

                }
                else if(input == 7)
                {

                    clear();
                }

        }while(input != 8);


        printf("Goodbye!\n\n");

    }
    
    return 0;
}

void clear()
{

    /*prints a new line 40 times until variable i is incrimented 40 times*/
    int i = 0;
    for( i ; i < 40 ; ++i)
    {

        printf("\n");
    }

}

void menu()
{

    //prints menu
    printf("Please select from the following options:\n");
    printf("1) Display the inventory.\n");
    printf("2) Price check.\n");
    printf("3) Display my shopping cart.\n");
    printf("4) Add to cart.\n");
    printf("5) Remove from cart.\n");
    printf("6) Check out.\n");
    printf("7) Clear Screen.\n");
    printf("8)Exit.\n\n");

}

int validate(int low, int high)
{


    int userInput = 0;
    int goodValue = 0;

    /*Keeps looping until the value entered by the user isnt between the range of 1-8*/
    do
    {
        /*accepts input from user and stores into variable called number*/
        scanf("%d", &userInput);

        /* checks to see if number is between 1-8*/
        if (userInput >= low && userInput <= high )
        {
            /*if above condition is true it gets stored into good val*/
            goodValue = userInput;
        }
        else
        {
            /*if condition is false it prints an error message*/
            printf("Invalid input, try again: ");
        }

    }while(goodValue != userInput);

        return userInput;

}



void displayInventory(const int sku[] , const float price[])
{

    printf("inventory\n");
    printf("=====================================\n");

    int i = 0;

    printf("Sku      Price\n");

    /*keeps looping until i is greator than the Maximum size of the inventory*/
    for(i=0 ; i < MAX_INVENTORY_SIZE ; i++)
    {

        /*Until the loop runs both arrays take values of i and inputs it as its element
        value and prints sku and price side by side*/
        printf("%d     %.2f \n", sku[i], price[i]) ;
    }

    printf("=====================================\n\n\n");

}



void checkPrice(const int sku[],const float price[])
{

    int input = 0;


    /*Asks user for the SKU number to find its price*/
    printf("Please input the sku number of the item: \n");
    scanf("%d", &input );

    int numOfArray=0;

    /*The SKU number entered by the user gets passed on to the function searchInventory*/
    numOfArray = searchInventory(sku , input);


    if(numOfArray != -1)
    {

        /*If the function searchInventory doesnt return -1 then it assumes that the SKU number
        entered but the user does match and it inputs that number into the sku array and price array
        and prints it out*/

        printf("Item %d costs $%.2f\n\n" ,sku[numOfArray] , price[numOfArray]);
    }
    else
    {
        /*if it does return -1 then it prompts the user that there was no match*/
        printf("Item does not exist in the shop! Please try again.!\n\n");
    }

}



int searchInventory(const int sku[],const int item)
{

    int num = 0;

        /*num keeps getting incrimented uptill the maximum inventory size*/
    for( num ; num < MAX_INVENTORY_SIZE ; num++)
    {

            /*If one of the num values which gets inputed into sku gets a match with item number which is
            essentially the index number of the element which is found and it returns the value num back*/
        if(sku[num] == item)
        {
                return num;
        }


    }
        return -1;

}



void displayCart(const struct Cart* pShoppingCart)
{
    int i;

    printf("\nShopping Cart\n");
    printf("=========================\n");
    printf("Sku   Quantity   Price   \n");

    for(i=0; i < pShoppingCart -> size; i++)
    {
        /*Uses i as the index value for both of the arrays. Accesses the myCart and gets the sku , quantity and price values and prints 
        corresponding values using i as the index */
        printf("%d     %d       %.2f \n" , pShoppingCart-> sku[i] , pShoppingCart -> quantity[i] , pShoppingCart -> price[i] );
    }

    printf("=========================\n\n");
}



void addCart(struct Cart* pShoppingCart,const int sku[],const float price[])
{
    int num=0;
    int i=0;
    int checkVal=0;
    int count=0;
    /*Keeps looping until the user does not enter the SKU value that exists in the inventory*/
    do{
        int input=0;

        printf("Please input a SKU number: ");
        scanf("%d",&input );
        /*Searches the searchInventory function and returns the index number of the sku number that the user enters*/
        checkVal = searchInventory(sku,input);

        if(checkVal != -1)
        {
            /*Promts user to enter the quantity of the SKU number and stores it in quantity array in the myCart struct.
            it uses the size number from the struct as the index */
            printf("Quantity: ");
            scanf("%d",&pShoppingCart->quantity[pShoppingCart -> size]);
            printf("The item is successfully added to the cart.\n\n\n");

            /*It points to price from myCart and in the bracket it uses the size as the index and it store the respective price and sku values and
            the index value returned from searchInventory function to find the values the user wants to store in the cart */
            pShoppingCart -> price[pShoppingCart->size]=price[checkVal];
            pShoppingCart->sku[pShoppingCart->size]=sku[checkVal];
            /*Increments size each time the if statement is correct therefore increasing the size of the shopping cart. size is used as the index value
            of all the arrays in myCart*/
            pShoppingCart -> size++ ;


        }
        else
        {
            printf("Item does not exist in the shop! Please try again.\n ");

        }

    }while(checkVal == -1);
}

void removeCart(struct Cart* pShoppingCart)
{
    /*Sets size to 0. Which means the index value for all arrays is 0 and that results in starting
    arrays all over again from index 0*/
    pShoppingCart->size = 0;
    printf("The cart is successfully removed!\n\n");
}


void checkout(struct Cart* pShoppingCart)
{
    float mul=0;
    float totalPrice=0;
    int i = 0;
    /*Runs for loop till the i is less than the size of the shopping cart*/
    for(i  ; i < pShoppingCart->size ; i++)
    {
        /*Multiplies value of price by its quantity and it uses i as its index value*/
        mul = (pShoppingCart -> price[i]) * (pShoppingCart -> quantity[i]);
        /*It keeps adding the multiplied value to its total value until loop stops running*/
        totalPrice = totalPrice + mul;
    }
    /*Stores totalPrice into the totalCost in myCart*/
    pShoppingCart->totalCost=totalPrice;
    printReceipt("receipt.dat",pShoppingCart);
}

int readInventory(const char filename[],int sku[],float price[])
{
    
    
    FILE *fp = NULL;
    int i=0;


    /*Opens the file by the name it recieves and sets it to read*/
    fp = fopen(filename,"r");
        
    if (fp != NULL)
    {
        /*loops until i is less than MAX_INVENTORY_SIZE which is 10*/
        for(i; i< MAX_INVENTORY_SIZE; i++)
        {
            /*uses i as the index value which makes both sku and price values parallel. It gets the input from the file
            stores the first value into the int sku[] array, it skips the comma and stores second value in the float price[] array*/
            fscanf(fp,"%d , %f", &sku[i], &price[i]);
        }
        /*closes the file*/
        fclose(fp);
        return 0;
    }
    else 
    {
        /*returns -1 if the file fails to open due to an error and the shopping cart program doesnt run and exits the program*/
        return -1;
    }
    
    return 0;
}


void printReceipt(const char filename[], struct Cart* pShoppingCart)
{
	FILE *file = NULL;

    /*opens the file and sets it to write*/
	file = fopen(filename , "w");

	if(file != NULL)
	{
        	   
        /*prints these statements to the file assigned*/
    	fprintf(file,"\nShopping Cart\n");
    	fprintf(file,"=========================\n");
    	fprintf(file,"Sku   Quantity   Price   \n");
    	
        /*For loop to incriment it until i is less than the size of the cart*/
        int i = 0;
        for(i; i < pShoppingCart -> size; i++)
    	   {
                /*Uses i as the index value for all of the arrays. Accesses the myCart and gets the sku , quantity and price values and prints 
                corresponding values using i as the index */
                fprintf(file,"%d     %d       %.2f \n" , pShoppingCart-> sku[i] , pShoppingCart -> quantity[i] , pShoppingCart -> price[i] );
   	        }	
	   
        fprintf(file,"=========================\n\n");
        fprintf(file,"The total price is sum = %.2f\n\n", pShoppingCart->totalCost);

        /*closes the file*/
        fclose(file);
    }
	
	
}

