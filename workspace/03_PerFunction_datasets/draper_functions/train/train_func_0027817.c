PopFocusFunction(
  void *theEnv)
  {
   struct defmodule *theModule;

   EnvArgCountCheck(theEnv,"pop-focus",EXACTLY,0);

   theModule = (struct defmodule *) EnvPopFocus(theEnv);
   if (theModule == NULL) return((SYMBOL_HN *) EnvFalseSymbol(theEnv));
   return(theModule->name);
  }
