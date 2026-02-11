PPInstanceCommand(
  void *theEnv)
  {
   INSTANCE_TYPE *ins;

   if (CheckCurrentMessage(theEnv,"ppinstance",TRUE) == FALSE)
     return;
   ins = GetActiveInstance(theEnv);
   if (ins->garbage == 1)
     return;
   PrintInstance(theEnv,WDISPLAY,ins,"\n");
   EnvPrintRouter(theEnv,WDISPLAY,"\n");
  }
