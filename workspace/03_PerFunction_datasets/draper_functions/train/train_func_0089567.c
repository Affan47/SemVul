PPConstruct(
  void *theEnv,
  char *constructName,
  char *logicalName,
  struct construct *constructClass)
  {
   void *constructPtr;


   constructPtr = (*constructClass->findFunction)(theEnv,constructName);
   if (constructPtr == NULL) return(FALSE);


   if ((*constructClass->getPPFormFunction)(theEnv,(struct constructHeader *) constructPtr) == NULL)
     { return(TRUE); }


   PrintInChunks(theEnv,logicalName,(*constructClass->getPPFormFunction)(theEnv,(struct constructHeader *) constructPtr));


   return(TRUE);
  }
