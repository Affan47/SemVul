t1_errno(void *args)
{
   int i;
   int *ret = (int *)args;

   *ret = 0;

   errno = 5;
   for (i = 0; i < 5; i++) {
      if (errno != 5) {
         fprintf(stderr, "t1: errno = %d\n", errno);
         *ret = 1;
         break;
      }
      sleep(1);
   }

   return NULL;
}
