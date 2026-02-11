ListConstruct(
  void *theEnv,
  struct construct *constructClass,
  char *logicalName,
  struct defmodule *theModule)
  {
   void *constructPtr;
   SYMBOL_HN *constructName;
   long count = 0;
   int allModules = FALSE;


   SaveCurrentModule(theEnv);


   if (theModule == NULL)
     {
      theModule = (struct defmodule *) EnvGetNextDefmodule(theEnv,NULL);
      allModules = TRUE;
     }


   while (theModule != NULL)
     {


      if (allModules)
        {
         EnvPrintRouter(theEnv,logicalName,EnvGetDefmoduleName(theEnv,theModule));
         EnvPrintRouter(theEnv,logicalName,":\n");
        }


      EnvSetCurrentModule(theEnv,(void *) theModule);


      for (constructPtr = (*constructClass->getNextItemFunction)(theEnv,NULL);
           constructPtr != NULL;
           constructPtr = (*constructClass->getNextItemFunction)(theEnv,constructPtr))
        {
         if (EvaluationData(theEnv)->HaltExecution == TRUE) return;

         constructName = (*constructClass->getConstructNameFunction)((struct constructHeader *) constructPtr);

         if (constructName != NULL)
           {
            if (allModules) EnvPrintRouter(theEnv,WDISPLAY,"   ");
            EnvPrintRouter(theEnv,logicalName,ValueToString(constructName));
            EnvPrintRouter(theEnv,logicalName,"\n");
           }

         count++;
        }


      if (allModules) theModule = (struct defmodule *) EnvGetNextDefmodule(theEnv,theModule);
      else theModule = NULL;
     }


   PrintTally(theEnv,WDISPLAY,count,constructClass->constructName,
                             constructClass->pluralName);

   RestoreCurrentModule(theEnv);
  }
