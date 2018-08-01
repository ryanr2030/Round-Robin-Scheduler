#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFERSIZE 4096

struct node {
	int pid;
	int runTime;
	struct node *next;
};

struct node *head=NULL;
struct node *tail=NULL;
void CreateList();
void ScanList(struct node *END);
void printList();
struct node* RemoveCurrent(struct node *current);

void add(int pid, int runTime);
int isEmpty();

static int listSize=0;
int main(){
	CreateList();
	printf("\n");
	ScanList(head);
	printf("\n\n");
	printf("ALL PROCESSES COMPLETE\n");

	
}

int isEmpty(){
		if(listSize==0)
			return 0;
		else
			return 1;
		
	}
void CreateList()
{
	FILE * fp;
	fp=fopen("/home/ryan/Desktop/CIS 340/Bartlett_Reynolds_CIS340_Project/Part 1/test2.txt", "r");
	char buffer[BUFFERSIZE];
	char line[2];
	char subs[100][100];
	int max=128;
	int i=0;
	int count=0;
	printf("\nStarting Process List:\n");
	while((fgets(subs[i], max, fp))!=NULL){
		printf("%s",subs[i]);
		i++;
		if(buffer!=""){
		count++;}
			
	}
	
	fclose(fp);
	//create each node then set tail==head at the end
	for (int i = 0; i<count; i++) {
		
		int pid=(subs[i][4])-'0';
		int runTime=(subs[i][6])-'0';
		add(pid, runTime);
	}
	tail->next=head;
	
}

//Traversal Method with process depreciation
void ScanList(struct node *END){
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	struct node *temp2 = (struct node*)malloc(sizeof(struct node));
	temp=END;
	int i=0,j=0;
	while(isEmpty()==1){
		if(temp==head && listSize!=1){
			printList();
		}
		if(head==tail){
			printf("\nPROCESS RUNNING: P(%d, %d) will run for 1 second.", head->pid, head->runTime);
		sleep(1);

		i=head->runTime;
		i--;
		head->runTime=i;
		if(i<=0){

			temp2=RemoveCurrent(head);

		}
		continue;
		}
		printf("\nPROCESS RUNNING: P(%d, %d) will run for 1 second.", temp->pid, temp->runTime);
		sleep(1);
		i=temp->runTime;
		i--;
		temp->runTime=i;
		
		if(i<=0){
			temp2=RemoveCurrent(temp);
		}

		temp=temp->next;
		
	}
		
}
//Traversal Method without process depreciation for printing
void printList(){
		struct node *current = head;
		printf("\n\nCPU ITERATION COMPLETE: Current process schedule\n");
		int i=0;
		while(i<listSize){
			printf("P(%d,%d), ",current->pid, current->runTime);
			current=current->next;
			i++;
		}
		
	


}


//Method to delete current node
struct node* RemoveCurrent(struct node *current){
	printf("\nPROCESS TERMINATION: P(%d) has finished its runtime!!!", current->pid);
	listSize--;

	struct node *temp=current->next;

	if(current==head){
		head->next=temp->next;
		head=temp;
		current=NULL;
		tail->next=head;
		return temp->next;
	}
	else if(current==tail){
		temp=head;
		while(temp->next!=current)
			temp=temp->next;
		tail=temp;
		temp->next=head;
		tail->next=head;
		
		current=NULL;
		return current;
	}
	while(temp->next!=current){
		temp=temp->next;
	}
	temp->next=current->next;
	current=NULL;

		
		
	return current;
}



//Method that adds a new node to the end of the list
void add(int pid, int runTime)
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->pid = pid;
    new_node->runTime=runTime;
    if(head==NULL){
	head=new_node;
    }		
    else{
        tail->next=new_node;
    }
    tail=new_node; 
    tail->next=head;
    printf("\nPROCESS ADDED: P(%d,%d) has been added to the linked list.",tail->pid, tail->runTime);
	listSize++;
    
}

