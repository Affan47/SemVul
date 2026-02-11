PPDefmodule(
  void *theEnv,
  char *defmoduleName,
  char *logicalName)
  {
   void *defmodulePtr;

   defmodulePtr = EnvFindDefmodule(theEnv,defmoduleName);
   if (defmodulePtr == NULL)
     {
      CantFindItemErrorMessage(theEnv,"defmodule",defmoduleName);
      return(FALSE);
     }

   if (EnvGetDefmodulePPForm(theEnv,defmodulePtr) == NULL) return(TRUE);
   PrintInChunks(theEnv,logicalName,EnvGetDefmodulePPForm(theEnv,defmodulePtr));
   return(TRUE);
  }
