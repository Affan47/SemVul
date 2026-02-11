Dependencies(
  void *theEnv,
  struct patternEntity *theEntity)
  {
   struct dependency *fdPtr;


   if (theEntity->dependents == NULL)
     {
      EnvPrintRouter(theEnv,WDISPLAY,"None\n");
      return;
     }


   for (fdPtr = (struct dependency *) theEntity->dependents;
        fdPtr != NULL;
        fdPtr = fdPtr->next)
     {
      if (GetHaltExecution(theEnv) == TRUE) return;
      PrintPartialMatch(theEnv,WDISPLAY,(struct partialMatch *) fdPtr->dPtr);
      EnvPrintRouter(theEnv,WDISPLAY,"\n");
     }
  }
