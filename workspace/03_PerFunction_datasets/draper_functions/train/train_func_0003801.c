EnvGetFactList(
  void *theEnv,
  DATA_OBJECT_PTR returnValue,
  void *vTheModule)
  {
   struct fact *theFact;
   unsigned long count;
   struct multifield *theList;
   struct defmodule *theModule = (struct defmodule *) vTheModule;


   SaveCurrentModule(theEnv);


   if (theModule == NULL)
     {
      for (theFact = (struct fact *) EnvGetNextFact(theEnv,NULL), count = 0;
           theFact != NULL;
           theFact = (struct fact *) EnvGetNextFact(theEnv,theFact), count++)
        {  }
     }
   else
     {
      EnvSetCurrentModule(theEnv,(void *) theModule);
      UpdateDeftemplateScope(theEnv);
      for (theFact = (struct fact *) GetNextFactInScope(theEnv,NULL), count = 0;
           theFact != NULL;
           theFact = (struct fact *) GetNextFactInScope(theEnv,theFact), count++)
        {  }
     }


   SetpType(returnValue,MULTIFIELD);
   SetpDOBegin(returnValue,1);
   SetpDOEnd(returnValue,(long) count);
   theList = (struct multifield *) EnvCreateMultifield(theEnv,count);
   SetpValue(returnValue,(void *) theList);


   if (theModule == NULL)
     {
      for (theFact = (struct fact *) EnvGetNextFact(theEnv,NULL), count = 1;
           theFact != NULL;
           theFact = (struct fact *) EnvGetNextFact(theEnv,theFact), count++)
        {
         SetMFType(theList,count,FACT_ADDRESS);
         SetMFValue(theList,count,(void *) theFact);
        }
     }
   else
     {
      for (theFact = (struct fact *) GetNextFactInScope(theEnv,NULL), count = 1;
           theFact != NULL;
           theFact = (struct fact *) GetNextFactInScope(theEnv,theFact), count++)
        {
         SetMFType(theList,count,FACT_ADDRESS);
         SetMFValue(theList,count,(void *) theFact);
        }
     }


   RestoreCurrentModule(theEnv);
   UpdateDeftemplateScope(theEnv);
  }
