/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include<string.h>
#define MAX 50
int top=-1;
int precedence(char c)
{
    if(c=='^')
      return 3;
    else if(c=='*'||c=='/'||c=='%')
      return 2;
    else if(c=='+'||c=='-')
      return 1;
    else 
    return -1;
}
char associativity(char c)
{
    if(c=='^')
      return 'R';
    else
      return 'L';
}
void infixToPostfix(char infix[], char postfix[])
{
    char stack[MAX], c;
    int index=0;
    for(int i=0;i<strlen(infix);i++)
    {
        c=infix[i];
        if(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9')
        {
            postfix[index++]=c;
        }
        else if(c=='(')
        {
            stack[++top]=c;
        }
        else if(c==')')
        {
            while(top>=0&&stack[top]!='(')
            {
                postfix[index++]=stack[top--];
            }
            top--;
        }
        else
        {
            while(top>=0&&(precedence(c)<precedence(stack[top])||(precedence(c)==precedence(stack[top])&&associativity(c)=='L')))
            {
                postfix[index++]=stack[top--];
            }
            stack[++top]=c;
        }
    }
    while(top>=0)
    {
        postfix[index++]=stack[top--];
    }
    postfix[index]='\0';
    printf("The postfix expression is : %s\n", postfix);
}
int compute(char symbol, int op1, int op2)
{
    int r;
    switch(symbol)
    {
        case '+':r=op2+op1;
        break;
        case '-':r=op2-op1;
        break;
        case '*':r=op2*op1;
        break;
        case '/':r=op2/op1;
        break;
        case '%':r=op2%op1;
        break;
        case '^':r=pow(op2,op1);
        break;
    }
    return r;
}
void evaluate(char postfix[])
{
    int stack[MAX], op1, op2, r;
    char symbol;
    for(int i=0;i<strlen(postfix);i++)
    {
        symbol=postfix[i];
        if(isdigit(symbol))
        {
            stack[++top]=symbol-'0';
        }
        else
        {
            op1=stack[top--];
            op2=stack[top--];
            r=compute(symbol,op1,op2);
            stack[++top]=r;
        }
    }
    printf("\nThe result is : %d\n", stack[top--]);
}
int main()
{
    char infix[MAX], postfix[MAX];
    int choice;
    do
    {
        printf("\n---Stack Based Expression Evaluator---\n");
        printf("\nMenu\n1. Conversion of Infix to Postfix Expression\n2. Evaluation of Postfix Expression\n3. Exit\n");
        printf("\nEnter the choice:");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:{
                printf("Enter the Infix expression:");
                scanf("%s", infix);
                infixToPostfix(infix,postfix);
            }
            break;
            case 2:{
                printf("Enter the Infix expression (digits only):");
                scanf("%s", infix);
                infixToPostfix(infix,postfix);
                evaluate(postfix);
            }
            break;
            case 3:printf("Exiting program\n");
            break;
            default:printf("Invalid choice\n");
        }
    
    }while(choice!=3);
    return 0;
}
