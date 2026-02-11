DestroyEnvironment(
  void *vtheEnvironment)
  {
   struct environmentCleanupFunction *cleanupPtr;
   int i;
   struct memoryData *theMemData;
   intBool rv = TRUE;
   struct environmentData *theEnvironment = (struct environmentData *) vtheEnvironment;

   if (EvaluationData(theEnvironment)->CurrentExpression != NULL)
     { return(FALSE); }

#if DEFRULE_CONSTRUCT
   if (EngineData(theEnvironment)->ExecutingRule != NULL)
     { return(FALSE); }
#endif

   theMemData = MemoryData(theEnvironment);

   EnvReleaseMem(theEnvironment,-1,FALSE);

   for (i = 0; i < MAXIMUM_ENVIRONMENT_POSITIONS; i++)
     {
      if (theEnvironment->cleanupFunctions[i] != NULL)
        { (*theEnvironment->cleanupFunctions[i])(theEnvironment); }
     }

   free(theEnvironment->cleanupFunctions);

   for (cleanupPtr = theEnvironment->listOfCleanupEnvironmentFunctions;
        cleanupPtr != NULL;
        cleanupPtr = cleanupPtr->next)
     { (*cleanupPtr->func)(theEnvironment); }

   RemoveEnvironmentCleanupFunctions(theEnvironment);

   EnvReleaseMem(theEnvironment,-1,FALSE);

#if ALLOW_ENVIRONMENT_GLOBALS
   RemoveHashedEnvironment(theEnvironment);
#endif

   if ((theMemData->MemoryAmount != 0) || (theMemData->MemoryCalls != 0))
     {
      printf("\n[ENVRNMNT8] Environment data not fully deallocated.\n");
      rv = FALSE;
     }

   free(theMemData->MemoryTable);

#if BLOCK_MEMORY
   ReturnAllBlocks(theEnvironment);
#endif

   for (i = 0; i < MAXIMUM_ENVIRONMENT_POSITIONS; i++)
     {
      if (theEnvironment->theData[i] != NULL)
        {
         free(theEnvironment->theData[i]);
         theEnvironment->theData[i] = NULL;
        }
     }

   free(theEnvironment->theData);

#if ALLOW_ENVIRONMENT_GLOBALS
   if (CurrentEnvironment == theEnvironment)
     { CurrentEnvironment = NULL; }
#endif

   free(theEnvironment);

   return(rv);
  }
