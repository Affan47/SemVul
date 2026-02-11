FindEnvironment(
  unsigned long environmentIndex)
  {
   struct environmentData *theEnvironment;
   unsigned long hashValue;

   hashValue = environmentIndex % SIZE_ENVIRONMENT_HASH;

   for (theEnvironment = EnvironmentHashTable[hashValue];
        theEnvironment != NULL;
        theEnvironment = theEnvironment->next)
     {
      if (theEnvironment->environmentIndex == environmentIndex)
        { return(theEnvironment); }
     }

   return(NULL);
  }
