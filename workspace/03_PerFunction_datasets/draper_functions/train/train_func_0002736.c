DeallocateTextProcessingData(
  void *theEnv)
  {
   struct lists *nextptr, *clptr;

   clptr = TextProcessingData(theEnv)->headings;
   while (clptr != NULL)
     {
      nextptr = clptr->next;

      TossFunction(theEnv,clptr->topics);
      rm(theEnv,(void *) clptr,(int) sizeof(struct lists));

      clptr = nextptr;
     }

#if HELP_FUNCTIONS
   if (TextProcessingData(theEnv)->help_file != NULL)
     {
      rm(theEnv,TextProcessingData(theEnv)->help_file,
         strlen(TextProcessingData(theEnv)->help_file) + 1);
     }
#endif
  }
