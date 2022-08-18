#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct node{
	char foodname[50];
	int quantity;
	float price;
	int data;
	struct node * next;
};

struct node *headc=NULL,*newnode,*tailc=NULL;
struct node *heada=NULL,*taila=NULL;
struct node *head_s;

void adminmenu(){
	printf("\n\t\t\t\t\t\t\t1.View total sales\n");
	printf("\t\t\t\t\t\t\t2.Add new items in the order menu\n");
	printf("\t\t\t\t\t\t\t3.Delete items from the order menu\n");
	printf("\t\t\t\t\t\t\t4.Display order menu\n");
	printf("\t\t\t\t\t\t\t5.Back to main menu\n\n");
	printf("\t\t\t\t\t\t\t  Enter your choice --->");
};

void customermenu(){
	printf("\n\t\t\t\t\t\t\t1.Place your order\n");
	printf("\t\t\t\t\t\t\t2.View your ordered items\n");
	printf("\t\t\t\t\t\t\t3.Delete an item from order\n");
	printf("\t\t\t\t\t\t\t4.Display final bill\n");
	printf("\t\t\t\t\t\t\t5.Back to main menu\n\n");
	printf("\t\t\t\t\t\t\t  Enter your choice --->");
};

struct node *createadmin(struct node *head,int data,char foodname[25],float price){
	newnode=(struct node*)malloc(sizeof(struct node));
	newnode->data=data;
	newnode->price=price;
	newnode->quantity=0;
	strcpy(newnode->foodname,foodname);
	newnode->next=NULL;
	struct node *temp;
	temp=head;
	if(head==NULL){
		heada=taila=newnode;
	}
	else{
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=newnode;
		taila=newnode;
	}
	return heada;
};

struct node* createcustomer(struct node *head,int data,int quantity){
	newnode=(struct node*)malloc(sizeof(struct node));
	struct node *temp=heada;
	int flag=0;
	while(temp!=NULL){
		if(temp->data==data){
			flag=1;
			break;
		}
		temp=temp->next;
	}
	if(flag==1){
		newnode->data=data;
		newnode->price=quantity*(temp->price);
		newnode->quantity=quantity;
		strcpy(newnode->foodname,temp->foodname);
		newnode->next=NULL;
		struct node *temp=head;
		
		if(temp==NULL){
			headc=tailc=newnode;
		}
		else{
			while(temp->next!=NULL){
				temp=temp->next;
			}
			temp->next=newnode;
			tailc=newnode;
		}
	}
	else{
		printf("\n\t\t\t\t\t\t\tThis item is not present in the menu!\n");
	}
	return headc;
};

void displaylist(struct node *head){
	struct node *temp1=head;
	if(temp1==NULL){
		printf("\n\t\t\t\t\t\t\tList is empty!!\n\n");
	}
	else{
		printf("\n");
		while(temp1!=NULL){
			if(temp1->quantity==0){
				printf("\t\t\t\t\t\t\t%d\t%s\t\t%0.2f\n",temp1->data,temp1->foodname,temp1->price);
			}
			else{
				printf("\t\t\t\t\t\t\t%d\t%s\t\t%d\t\t%0.2f\n",temp1->data,temp1->foodname,temp1->quantity,temp1->price);
			}
			temp1=temp1->next;
		}
		printf("\n");
	}
};

struct node *totalsales(int data,int quantity){
	newnode=(struct node*)malloc(sizeof(struct node));
	int flag=0;
	struct node *temp=heada;
	while(temp->data!=data){
		temp=temp->next;
	}
	newnode->data=data;
	newnode->price=quantity*(temp->price);
	newnode->quantity=quantity;
	strcpy(newnode->foodname,temp->foodname);
	newnode->next=NULL;
	
	struct node *temp1=head_s;
	
	if(temp1==NULL){
		head_s=newnode;
	}
	else
	{
		while(temp1->next!=NULL){
			if(temp1->data=data){
				flag=1;
				break;
			}
			temp1=temp1->next;
		}
		if(flag==1){
			temp1->quantity+=newnode->quantity;
			temp1->price+=newnode->price;
		}
		else{
			temp1->next=newnode;
		}
	}
	return head_s;
};

void calculatetotalsales(){
	struct node *temp=headc;
	while(temp!=NULL){
		head_s=totalsales(temp->data,temp->quantity);
		temp=temp->next;
	}
};

struct node *delete(int data,struct node *head,struct node *tail){
	if(head==NULL){
		printf("\n\t\t\t\t\t\t\tList is empty\n");
	}
	else{
		struct node *temp;
		if(data==head->data){
			temp=head;
			head=head->next;
			free(temp);
		}
		else if(data==tail->data){
			temp=tail;
			tail->next=NULL;
			free(temp);
		}
		else{
			temp=head;
			struct node* temp1=temp;
			while(data!=temp->data){
				temp1=temp;
				temp=temp->next;
			}
			temp1->next=temp->next;
			free(temp);
		}
	}
};

int deleteadmin(){
	printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
	int num;
	scanf("%d",&num);
	
	struct node *temp=heada;
	while(temp!=NULL){
		if(temp->data==num){
			heada=delete(num,heada,taila);
			return 1;
		}
		temp=temp->next;
	}
	return 0;
};

int deletecustomer(){
	printf("\n\t\t\t\t\tEnter serial no.of the food item which is to be deleted: ");
	int num;
	scanf("%d",&num);
	
	struct node *temp=headc;
	while(temp!=NULL){
		if(temp->data==num){
			headc=delete(num,headc,tailc);
			return 1;
		}
		temp=temp->next;
	}
	return 0;
};

void displaybill(){
	displaylist(headc);
	struct node *temp=headc;
	float total_price=0;
	while(temp!=NULL){
		total_price+=(temp->quantity)*(temp->price);
		temp=temp->next;
	}
	printf("\t\t\t\t\t\t\tTotal price: %0.02f\n",total_price);
};

struct node *deletelist(struct node *head){
	if(head==NULL){
		return NULL;
	}
	else{
		struct node *n,*temp=head;
		while(temp!=NULL){
			n=temp->next;
			free(temp);
			temp=n;
		}
		head=NULL;
	}
	return head;
};

void admin(){
	printf("\n\t\t\t\t\t -----------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t            ADMIN SECTION\n");
	printf("\t\t\t\t\t   -----------------------------------------------------\n");
	while(1){
		adminmenu();
		int opt;
		scanf("%d",&opt);
		if(opt==5){
			break;
		}
		
		switch(opt){
			case 1:displaylist(head_s);
				   break;
			case 2:printf("\n\t\t\t\t\t\t\tEnter serial no. of the food item: ");
				   int num,flag=0;
				   char name[50];
				   float price;
				   scanf("%d,&num");
				   
				   struct node *temp=heada;
				   
				   while(temp!=NULL)
				   {
				   	if(temp->data==num)
				   	{
				   		printf("\n\t\t\t\t\t\t\tFood item with given serial number already exists!!\n\n");
				   		flag=1;
				   		break;
					}
					temp=temp->next;   
				   }
				   if(flag==1){
				   	break;
				   }
				   printf("\t\t\t\t\t\t\tEnter food item name: ");
				   scanf("%s",&name);
				   printf("\t\t\t\t\t\t\tEnter price: ");
				   scanf("%d",&price);
				   heada=createadmin(heada,num,name,price);
				   printf("\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n");
				   break;
			case 3:if(deleteadmin()){
				        printf("\n\t\t\t\t\t\t\t### Update list of food items menu ###\n");
					    break;
					}
					else{
						printf("\n\t\t\t\t\t\tFood items with the given serial number doesnt exist\n\n");
					}
					break;
			case 4:printf("\n\t\t\t\t\t\t    ### Order menu ###\n");
				   displaylist(heada);
				   break;
			default:printf("\n\t\t\t\t\t\tWong Input!! please choose valid option\n");
				    break;
		}
	}
};

void customer(){
	int flag=0,j=1;
	char ch;
	printf("\n\t\t\t\t\t  -------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t        CUSTOMER SECTION\n");
	printf("\t\t\t\t\t\t  --------------------------------------------------------------------\n");
	while(1){
		customermenu();
		int opt;
		scanf("%d",&opt);
		
		if(opt==5)
			break;
		switch(opt){
			case 1:displaylist(heada);
				   printf("\n\t\t\t\t\t\tEnter the number corresponding to the item you want to order: ");
				   int n;
				   scanf("%d",&n);
				   printf("\t\t\t\t\t\tEnter quantity: ");
				   int quantity;
				   scanf("%d",&quantity);
				   headc=createcustomer(headc,n,quantity);
				   break;
			case 2:printf("\n\t\t\t\t\t\t\t  ###List of ordered items  ###\n");
				   displaylist(headc);
				   break;
			case 3:if(deletecustomer()){
						printf("\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n");
						displaylist(headc);
					}
					else
						printf("\n\t\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n");
					break;
			case 4:calculatetotalsales();
				   printf("\n\t\t\t\t\t\t\t  ### Final Bill ###\n");
				   displaybill();
				   headc=deletelist(headc);
				   printf("\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t");
				   fflush(stdin);
				   ch=fgetc(stdin);
				   flag=1;
				   break;
			default:printf("\n\t\t\t\t\t\tWrong Input !! Please choose valid option\n");
				    break;
			}
			if(flag==1)
				break;
			}
};

int mainmenu()
{
	printf("\n									**************************************************************************************\n");
	printf("                                               					WELCOME TO RESTAURANT MANAGEMENT\n");
	printf("									**************************************************************************************\n");
	printf("\t\t\t\t\t\t\t1.ADMIN SECTION--->\n");
	printf("\t\t\t\t\t\t\t2.CUSTOMER SECTION--->\n");
	printf("\t\t\t\t\t\t\t3.EXIT--->\n\n");
	printf("\t\t\t\t\t\t\tEnter your choice--->");
}

int main(){
	heada=createadmin(heada,1,"Hot and Sour Soup",100);
	heada=createadmin(heada,2,"Machow Soup",200);
	heada=createadmin(heada,3,"Manchurian Noddles",150);
	heada=createadmin(heada,4,"Fried Rice",180);
	heada=createadmin(heada,5,"Hakka Noodles",80);
	
	while(1){
		mainmenu();
		int choice;
		scanf("%d",&choice);
		
		if(choice==3){
			printf("\n\t\t\t\t\t\t\t****************Thank You!!******************\n");
			break;
		}
		switch(choice){
			case 1:admin();
				   break;
			case 2:customer();
				   break;
			case 3:break;
			default:printf("\n\t\t\t\t\t\tWrong Input !! please choose valid option\n");
				    break;
		}
	}
}
