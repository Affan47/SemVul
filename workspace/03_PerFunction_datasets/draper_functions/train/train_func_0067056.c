ClearCommand(
  void *theEnv)
  {
   if (EnvArgCountCheck(theEnv,"clear",EXACTLY,0) == -1) return;
   EnvClear(theEnv);
   return;
  }
