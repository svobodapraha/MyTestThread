#include <signal.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


void my_handler(int s)
{
  fprintf(stderr, "exit");
  exit(1);
}


/* Prints x’s to stderr.  The parameter is unused.  Does not return.  */
pthread_mutex_t PrintMutex;




void* print_xs (void* unused)
{
  while (1) 
  {
    usleep(3 * 1000);
    pthread_mutex_lock(&PrintMutex);
    fprintf (stderr, "123");
    fprintf (stderr, "456");
    fprintf (stderr, "789\n");
    pthread_mutex_unlock(&PrintMutex);
  }
  return NULL;
}
/* The main program.  */
int main ()
{
  pthread_mutex_init (&PrintMutex, NULL);
  pthread_t thread_id;
  signal(SIGINT, my_handler);
  /* Create a new thread.  The new thread will run the print_xs
   function.  */
  pthread_create (&thread_id, NULL, &print_xs, NULL);
  /* Print o’s continuously to stderr.  */
  while (1)
  {
    pthread_mutex_lock(&PrintMutex);
    fprintf (stderr, "abc");
    fprintf (stderr, "def");
    fprintf (stderr, "ghi");
    fprintf (stderr, "jkl");
    fprintf (stderr, "mno");
    fprintf (stderr, "pqr");
    fprintf (stderr, "stu");
    fprintf (stderr, "vwx");
    fprintf (stderr, "yz\n");
    pthread_mutex_unlock(&PrintMutex);
    //usleep(1 * 1000);
  }
  return 0;
}