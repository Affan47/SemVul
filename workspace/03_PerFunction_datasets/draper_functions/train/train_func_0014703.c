PrintInstanceLongForm(
  void *theEnv,
  char *logName,
  void *vins)
  {
   INSTANCE_TYPE *ins = (INSTANCE_TYPE *) vins;

   if (PrintUtilityData(theEnv)->InstanceAddressesToNames)
     {
      if (ins == &InstanceData(theEnv)->DummyInstance)
        EnvPrintRouter(theEnv,logName,"\"<Dummy Instance>\"");
      else
        {
         EnvPrintRouter(theEnv,logName,"[");
         EnvPrintRouter(theEnv,logName,ValueToString(GetFullInstanceName(theEnv,ins)));
         EnvPrintRouter(theEnv,logName,"]");
        }
     }
   else
     {
      if (PrintUtilityData(theEnv)->AddressesToStrings)
        EnvPrintRouter(theEnv,logName,"\"");
      if (ins == &InstanceData(theEnv)->DummyInstance)
        EnvPrintRouter(theEnv,logName,"<Dummy Instance>");
      else if (ins->garbage)
        {
         EnvPrintRouter(theEnv,logName,"<Stale Instance-");
         EnvPrintRouter(theEnv,logName,ValueToString(ins->name));
         EnvPrintRouter(theEnv,logName,">");
        }
      else
        {
         EnvPrintRouter(theEnv,logName,"<Instance-");
         EnvPrintRouter(theEnv,logName,ValueToString(GetFullInstanceName(theEnv,ins)));
         EnvPrintRouter(theEnv,logName,">");
        }
      if (PrintUtilityData(theEnv)->AddressesToStrings)
        EnvPrintRouter(theEnv,logName,"\"");
     }
  }
