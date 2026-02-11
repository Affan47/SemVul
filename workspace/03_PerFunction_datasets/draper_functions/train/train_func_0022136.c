EnvFocus(
  void *theEnv,
  void *vTheModule)
  {
   struct defmodule *theModule = (struct defmodule *) vTheModule;
   struct focus *tempFocus;


   EnvSetCurrentModule(theEnv,(void *) theModule);
   if (EngineData(theEnv)->CurrentFocus != NULL)
     { if (EngineData(theEnv)->CurrentFocus->theModule == theModule) return; }


#if DEBUGGING_FUNCTIONS
   if (EngineData(theEnv)->WatchFocus)
     {
      EnvPrintRouter(theEnv,WTRACE,"==> Focus ");
      EnvPrintRouter(theEnv,WTRACE,ValueToString(theModule->name));
      if (EngineData(theEnv)->CurrentFocus != NULL)
        {
         EnvPrintRouter(theEnv,WTRACE," from ");
         EnvPrintRouter(theEnv,WTRACE,ValueToString(EngineData(theEnv)->CurrentFocus->theModule->name));
        }
      EnvPrintRouter(theEnv,WTRACE,"\n");
     }
#endif


   tempFocus = get_struct(theEnv,focus);
   tempFocus->theModule = theModule;
   tempFocus->theDefruleModule = GetDefruleModuleItem(theEnv,theModule);
   tempFocus->next = EngineData(theEnv)->CurrentFocus;
   EngineData(theEnv)->CurrentFocus = tempFocus;
   EngineData(theEnv)->FocusChanged = TRUE;
  }
