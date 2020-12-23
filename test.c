#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

//Exponential algoritm
void Hanoi(int n,int from,int to,int aux){
	if(n==1){
		return;
	}
	Hanoi(n-1,from,aux,to);
	Hanoi(n-1,aux,to,from);
}
int main(){
	struct timeval initial,final;
	pid_t pid;
	pid=fork();
	//If fork has failed
	if(pid<0){
		perror("fork");
	}
	if(pid!=0){
	//Providing Priority to child
		int status=syscall(548,pid,1000000);
		if(status<0){
			perror("In System error has occured");
		}
		//Line written so that the parent gets it's priority before the execution of Hanoi(31,1,2,3)
		for(int i=0;i<100000000;i++);
	}
	if(pid==0){
		//child Process
		gettimeofday(&initial,NULL);
		Hanoi(28,1,2,3);
		gettimeofday(&final,NULL);
		printf("Child takes %lfs to complete\n",(double)(final.tv_sec-initial.tv_sec)+(double)(final.tv_usec-initial.tv_usec)/1000000L);
	}
	else{
		
		//Parent Process
		gettimeofday(&initial,NULL);
		Hanoi(28,1,2,3);
		gettimeofday(&final,NULL);
		printf("Parent takes %lfs to complete\n",(double)(final.tv_sec-initial.tv_sec)+(double)(final.tv_usec-initial.tv_usec)/1000000L);
		wait(NULL);//Child Reaper 		
	}
}
