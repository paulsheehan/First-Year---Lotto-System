#include <stdio.h>
#include <conio.h>
#define SIZE 6

void scan_chosen_num (int *chosen_num, int *bonus_num);
/* User enters chosen lotto numbers into array, between 1 - 42 */

void print_chosen (int *chosen_num, int *bonus_num);
/* Prints users chosen numbers */

void bubble_sort_chosen (int *chosen_num);
/* Sorts chosen numbers in order of value  */

void compare_results (int *chosen_num, int *winning, int *bonus_num);
/* Compare chosen numbers with winning numbers and print results */

void accumulator (int *chosen_num, int *bonus_num, int *accumulator);
/* Displays the frequency of each chosen number */


// MAIN  
main()
{
    int winning[SIZE] = {1,3,5,7,9,11};
    int choice[SIZE];
    static int numbers[42] = {0};
    char cont = 'n'; 
    int bonus, menu_option = 0, i;
    
    
    
    printf("Welcome to the Lotto game. You will pick your 6 numbers and a bonus number and win up to 500,000 Euro. Good luck!\n\n");
    
    //User choses numbers before menu is displayed
    scan_chosen_num(choice, &bonus);
    
    //Numbers are sorted in increasing order
    bubble_sort_chosen(choice);
    
    clrscr();
    
    while (cont == 'n')
    {
        
        printf("MENU\nPress 1 - 5 to choose options:\n1.Choose new numbers\n2.See your current chosen numbers\n3.See results"\
        "\n4.See frequency of chosen numbers\n5.Quit the Lotto game!");
        
        scanf("%d", &menu_option);
        
        //Each case calls a specific function which the user chooses
        switch(menu_option)
        {
            case 1:             //Choose new numbers
            {
                clrscr();
                scan_chosen_num(choice, &bonus);
                print_chosen(choice, &bonus);
                bubble_sort_chosen(choice);
                break;
            }
            
            case 2:             //Prints numbers
            {
                clrscr();
                
                print_chosen(choice, &bonus);
                break;
            }
            
            case 3:             //Compares chosen numbers to winning numbers and displays results
            {
                clrscr();
                
                compare_results(choice, winning, &bonus);
                break;
            }
            
            case 4:             //Displays the frequency of the numbers the user entered
            {
                clrscr();
                
                accumulator (choice, &bonus, numbers);
                break;
            }
            
            case 5:             //Quits program
            {
                clrscr();
                
                printf("Are you sure you want to quit? (y or n)\n\n");
                //If user chooses "n" the program will reiterate, if "y" exit while loop and end program
                scanf("%1s", &cont);
                clrscr();
                break;
            }
            
            default:
            {
                clrscr();
                printf("Invallid option!");
                break;
            }
        }
        
    }
    
    //Winning numbers are displayed when the user ends the program
    printf("The winning lotto numbers were:");
    
    for(i = 0; i < SIZE; i++)
    {
        printf(" %d", winning[i]);
    }

    getch();
    
}
// END MAIN 



void scan_chosen_num (int *chosen_num, int *bonus_num)
{
    int i, j, error;
    
    
    do
    {
        
        printf("Please enter your 6 chosen lotto numbers, numbers must be from 1 to 42:\n");
        
        
        error = 0;
        
        for(i=0; i < SIZE; i++)
        {
            scanf("%d", &chosen_num[i]);
        }
        
        
        for(i=0; i < SIZE; i++)
        {
            for(j=1; j < SIZE; j++)
            {
                //Each chosen number is compared with itself 6^2 times
                if(chosen_num[i] == chosen_num[j])
                {   
                    //If the two chosen numbers are equal, but not the same element of the array, an error is displayed and "error" is incremented
                    if(i != j)
                    {
                        printf("ERROR: %d was entered multiple times\n", chosen_num[i]);
                        error++;
                    }
                    
                }
                
            }
            
        }
        
        printf("\n\nNow enter your bonus lotto number: ");
        scanf("%d", &(*bonus_num));
        
        for(i=0; i < SIZE; i++)
        {
            //If the users chosen numbers are not between 1 and 42 error is incremented
            if(chosen_num[i] > 42 || chosen_num[i] < 1)
            {
                printf("\nERROR: Chosen number %d is invallid, please try again\n", chosen_num[i]);
                error++;
            }
        }
        
        if (*bonus_num > 42 || *bonus_num < 1)
        {
            printf("\nChosen number %d invallid, please try again\n", *bonus_num);
            error++;
        } 
        
        //If error was incremented the while loop reiterates, when he user reaches an error, the process will not loop untill the user has entered all their numbers
    } while(error > 0);
    
}


void print_chosen (int *chosen_num, int *bonus_num)
{
    int i;
    
    printf("\n");
    
    printf ("Your chosen numbers are:");
    //Prints users chosen numbers
    for(i=0; i < SIZE; i++)
    {
        printf (" %d", chosen_num[i]);
    }
    
    printf("\nBonus number: %d\n\n", *bonus_num);
}



void bubble_sort_chosen (int *chosen_num)
{
    int i, j, temp;
    
    for(i=0; i < SIZE; i++)
    {
        //Users chosn numbers are compared 
        for(j=1; j < SIZE; j++)
        {
            //If a number is greater than the next, temp is used as a pivot and the two numbers are swapped 
            if(chosen_num[i] > chosen_num[j])
            {
                temp = chosen_num[i];
                chosen_num[i] = chosen_num[j];
                chosen_num[j] = temp;
            }
        }
        
    }
    
}



void compare_results (int *chosen_num, int *winning, int *bonus_num)
{
    int i, j, winning_nums = 0;
    int winning_bonus = 42;
    
    for(i=0; i < SIZE; i++)
    {
        for(j=0; j < SIZE; j++)
        //Each of the users chosen numbers are compared to the winning numbers
        {
            //If the users number matches the winning number then winning_nums is incremented 
            if (chosen_num[i] == winning[j])
            {
                winning_nums++;
            }
        }
        
    }
    
    printf("\n\nYou got %d numbers right\n\n", winning_nums);
    
    //If the user has enough matched numbers and the bonus number is right then winning number becomes 7, 8 or 9
    if (*bonus_num == winning_bonus && winning_nums == 3)
    { 
        winning_nums = 7;
    }
    
    if (*bonus_num == winning_bonus && winning_nums == 4)
    {
        winning_nums = 8;
    }
    if (*bonus_num == winning_bonus && winning_nums == 5)
    {
        winning_nums = 9;
    }
    
    switch (winning_nums)
    {       
        case 4:
        {
            printf("You win a full tank of petrol!\n\n");
            break;
        }
        case 5:
        {
            printf("You have won a paid, all inclusive holiday!\n\n");
            break;
        }
        case 6:
        {
            printf("Jackpot! You have won 500,000 Euro!\n\n");
            break;
        }
        
        case 7: //Match 3 + Bonus
        {
            printf("You get a free lotto scratch card.\n\n");
            break;
        }
        case 8: //Match 4 + Bonus
        {
            printf("You have won a paid night out.\n\n");
            break;
        }
        case 9: //  Match 5 + bonus
        {
            printf("Almost - just 1 away from the jackpot! You have won a Jaguar XK convertable!\n\n");
            break;
        }
        default:
        {
           printf("You did not win anything; hard luck!\n\n"); 
        }
    }
    
}


void accumulator (int *chosen_num, int *bonus_num, int *num_count)
{
    int i, j;
    
    for(i = 0; i < SIZE;i++)
    {
        for(j = -1; j < SIZE;j++)
        {
            num_count[j]++;
        }
        printf("Number %d was chosen %d times\n", chosen_num[i], num_count[i]);
    }
    
    printf("Bonus number %d was chosen %d times\n\n", *bonus_num, num_count[1]);
    
}
