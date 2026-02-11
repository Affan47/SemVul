PrintFactIdentifierInLongForm(
  void *theEnv,
  char *logicalName,
  void *factPtr)
  {
   if (PrintUtilityData(theEnv)->AddressesToStrings) EnvPrintRouter(theEnv,logicalName,"\"");
   if (factPtr != (void *) &FactData(theEnv)->DummyFact)
     {
      EnvPrintRouter(theEnv,logicalName,"<Fact-");
      PrintLongInteger(theEnv,logicalName,((struct fact *) factPtr)->factIndex);
      EnvPrintRouter(theEnv,logicalName,">");
     }
   else
     { EnvPrintRouter(theEnv,logicalName,"<Dummy Fact>"); }

   if (PrintUtilityData(theEnv)->AddressesToStrings) EnvPrintRouter(theEnv,logicalName,"\"");
  }
