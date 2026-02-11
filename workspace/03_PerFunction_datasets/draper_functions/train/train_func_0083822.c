ClearBload(
  void *theEnv)
  {
   long i;
   unsigned long space;
   struct portItem *theList;


   for (i = 0; i < DefmoduleData(theEnv)->BNumberOfDefmodules; i++)
     {
      DecrementSymbolCount(theEnv,DefmoduleData(theEnv)->DefmoduleArray[i].name);
      for (theList = DefmoduleData(theEnv)->DefmoduleArray[i].importList;
           theList != NULL;
           theList = theList->next)
        {
         if (theList->moduleName != NULL) DecrementSymbolCount(theEnv,theList->moduleName);
         if (theList->constructType != NULL) DecrementSymbolCount(theEnv,theList->constructType);
         if (theList->constructName != NULL) DecrementSymbolCount(theEnv,theList->constructName);
        }

      for (theList = DefmoduleData(theEnv)->DefmoduleArray[i].exportList;
           theList != NULL;
           theList = theList->next)
        {
         if (theList->moduleName != NULL) DecrementSymbolCount(theEnv,theList->moduleName);
         if (theList->constructType != NULL) DecrementSymbolCount(theEnv,theList->constructType);
         if (theList->constructName != NULL) DecrementSymbolCount(theEnv,theList->constructName);
        }

      rm(theEnv,DefmoduleData(theEnv)->DefmoduleArray[i].itemsArray,sizeof(void *) * GetNumberOfModuleItems(theEnv));
     }


   space = DefmoduleData(theEnv)->BNumberOfDefmodules * sizeof(struct defmodule);
   if (space != 0) genlongfree(theEnv,(void *) DefmoduleData(theEnv)->DefmoduleArray,space);
   DefmoduleData(theEnv)->BNumberOfDefmodules = 0;


   space = DefmoduleData(theEnv)->NumberOfPortItems * sizeof(struct portItem);
   if (space != 0) genlongfree(theEnv,(void *) DefmoduleData(theEnv)->PortItemArray,space);
   DefmoduleData(theEnv)->NumberOfPortItems = 0;


   SetListOfDefmodules(theEnv,NULL);
   CreateMainModule(theEnv);
   DefmoduleData(theEnv)->MainModuleRedefinable = TRUE;
  }
