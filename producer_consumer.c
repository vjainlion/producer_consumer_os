/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t mutex,empty,full;
int next_produce[12];

int i = 0;
void *producer(void *arg)
{
   int t;
  t = ((int)arg);

    sem_wait(&empty);
    sem_wait(&mutex);
    next_produce[i] = t;
    printf("producer %d th has produced %d th item\n",t,next_produce[i]);
    i++;
    sem_post(&mutex);
    sem_post(&full);


}

void *consumer(void *arg)
{
    int t = (int)arg;
    sem_wait(&full);
    sem_wait(&mutex);

    printf("Consumer %d th is consuming %dth item from buffer\n",t,next_produce[--i]);

    sem_post(&mutex);

    sem_post(&empty);


}

int main()
{
    int i;
    pthread_t ptid[13],ctid[13];

    sem_init(&mutex,0,1);
    sem_init(&empty,0,12);
    sem_init(&full,0,0);

    for(i=0;i<=12;i++)
    {
        pthread_create(&ptid[i],NULL,producer,(void *)i);
        pthread_create(&ctid[i],NULL,consumer,(void *)i);

    }
    for(i=0;i<=12;i++)
    {
        pthread_join(ptid[i],NULL);
        pthread_join(ctid[i],NULL);
    }

    return 0;
}
