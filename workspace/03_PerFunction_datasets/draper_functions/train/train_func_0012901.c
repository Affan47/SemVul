find_process_index(process_set *pset, int tid)
{
   int i = pset->procnum-1, *procs = pset->procs;

   for ( ; i >= 0 && procs[i] != tid; i--);
#ifdef DO_TESTS
   if (i == -1){
      printf("TM: process index not found !!!\n\n");
      exit(-5);
   }
#endif
   return(i);
}
