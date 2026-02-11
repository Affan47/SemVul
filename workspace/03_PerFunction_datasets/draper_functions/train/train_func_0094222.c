alloc_minutiae(MINUTIAE **ominutiae, const int max_minutiae)
{
   MINUTIAE *minutiae;

   minutiae = (MINUTIAE *)malloc(sizeof(MINUTIAE));
   if(minutiae == (MINUTIAE *)NULL){
      fprintf(stderr, "ERROR : alloc_minutiae : malloc : minutiae\n");
      exit(-430);
   }
   minutiae->list = (MINUTIA **)malloc(max_minutiae * sizeof(MINUTIA *));
   if(minutiae->list == (MINUTIA **)NULL){
      fprintf(stderr, "ERROR : alloc_minutiae : malloc : minutiae->list\n");
      exit(-431);
   }

   minutiae->alloc = max_minutiae;
   minutiae->num = 0;

   *ominutiae = minutiae;
   return(0);
}
