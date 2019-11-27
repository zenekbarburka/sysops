
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define SIGRTMIN = 0;

pid_t child_pid;

int while_loop_condition = 1;

int l = 100;
int sent = 0;
int received = 0;

void au1(int sig_no) {

    received++;
};


void au2(int sig_no) {

    exit(0);
};


void au3(int sig_no) {

    // child case

    if (child_pid > 0) {

      kill(child_pid,SIGUSR2);
    }

    // parent case

    exit(0);

};


void au4(int sig_no) {

    exit(0);
};


void T1(){

    child_pid = fork();

    while (while_loop_condition) {

        if (child_pid > 0) {

            if (sent < l) {

                int to_be_sent = sent + 1;

                printf("-------------------PARENT SENDING SIGUSR1 #%d\n",to_be_sent);

                kill(child_pid,SIGUSR1);

                sent++;

                printf("sent by parent: %d \n",sent);
                printf("received by parent: %d \n",received);


            } else {

                printf("-------------------PARENT SENDING SIGUSR2 TO FINISH \n");
                kill(child_pid,SIGUSR2);
                while_loop_condition = 0;
            }

        } else if (child_pid == 0) {



            if ((received - sent) > 0) {

                printf("received by child: %d \n",received);
                int to_be_sent = sent + 1;
                printf("-------------------CHILD SENDING SIGUSR1 #%d\n",to_be_sent);
                pid_t parnet = getppid();
                kill(parnet, SIGUSR1);
                sent++;
                printf("sent by child: %d \n",sent);

            }


        }


    }

    printf("exit from the loop \n");


};

void T2(){

    child_pid = fork();

    while (while_loop_condition) {

        if (child_pid > 0) {

            if (sent < l && received == sent) {

                int to_be_sent = sent + 1;

                printf("-------------------PARENT SENDING SIGUSR1 #%d\n",to_be_sent);

                kill(child_pid,SIGUSR1);

                sent++;

                printf("sent by parent: %d \n",sent);
                printf("received by parent: %d \n",received);


            } else if (sent == l){

                printf("-------------------PARENT SENDING SIGUSR2 TO FINISH \n");
                kill(child_pid,SIGUSR2);
                while_loop_condition = 0;
            }

        } else if (child_pid == 0) {



            if ((received - sent) > 0) {

                printf("received by child: %d \n",received);
                int to_be_sent = sent + 1;
                printf("-------------------CHILD SENDING SIGUSR1 #%d\n",to_be_sent);
                pid_t parnet = getppid();
                kill(parnet, SIGUSR1);
                sent++;
                printf("sent by child: %d \n",sent);

            }


        }


    }

    printf("exit from the loop \n");



}









int main(){

    struct sigaction act1;
    act1.sa_handler = au1;
    sigemptyset(&act1.sa_mask);
    act1.sa_flags = 0;
    sigaction(SIGUSR1, &act1, NULL);


    struct sigaction act2;
    act2.sa_handler = au2;
    sigemptyset(&act2.sa_mask);
    act2.sa_flags = 0;
    sigaction(SIGUSR2, &act2, NULL);


    struct sigaction act3;
    act3.sa_handler = au3;
    sigemptyset(&act3.sa_mask);
    act3.sa_flags = 0;
    sigaction(SIGINT, &act3, NULL);


    struct sigaction act4;
    act4.sa_handler = au4;
    sigemptyset(&act3.sa_mask);
    act4.sa_flags = 0;
    sigaction((SIGRTMIN+1), &act4, NULL);








    //T1();

    child_pid = fork();

    while (while_loop_condition) {

        if (child_pid > 0) {

            if (sent < l && received == sent) {

                int to_be_sent = sent + 1;

                printf("-------------------PARENT SENDING SIGUSR1 #%d\n",to_be_sent);

                kill(child_pid,SIGUSR1);

                sent++;

                printf("sent by parent: %d \n",sent);
                printf("received by parent: %d \n",received);


            } else if (sent == l){

                printf("-------------------PARENT SENDING SIGUSR2 TO FINISH \n");
                kill(child_pid,SIGUSR2);
                while_loop_condition = 0;
            }

        } else if (child_pid == 0) {



            if ((received - sent) > 0) {

                printf("received by child: %d \n",received);
                int to_be_sent = sent + 1;
                printf("-------------------CHILD SENDING SIGUSR1 #%d\n",to_be_sent);
                pid_t parnet = getppid();
                kill(parnet, SIGUSR1);
                sent++;
                printf("sent by child: %d \n",sent);

            }


        }


    }

    printf("exit from the loop \n");









};