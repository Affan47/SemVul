ConstraintConflictMessage(
  void *theEnv,
  struct symbolHashNode *variableName,
  int thePattern,
  int theField,
  struct symbolHashNode *theSlot)
  {


   PrintErrorID(theEnv,"RULECSTR",1,TRUE);


   if (variableName != NULL)
     {
      EnvPrintRouter(theEnv,WERROR,"Variable ?");
      EnvPrintRouter(theEnv,WERROR,ValueToString(variableName));
      EnvPrintRouter(theEnv,WERROR," in CE #");
      PrintLongInteger(theEnv,WERROR,(long int) thePattern);
     }
   else
     {
      EnvPrintRouter(theEnv,WERROR,"Pattern #");
      PrintLongInteger(theEnv,WERROR,(long int) thePattern);
     }


   if (theSlot == NULL)
     {
      EnvPrintRouter(theEnv,WERROR," field #");
      PrintLongInteger(theEnv,WERROR,(long int) theField);
     }
   else
     {
      EnvPrintRouter(theEnv,WERROR," slot ");
      EnvPrintRouter(theEnv,WERROR,ValueToString(theSlot));
     }


   EnvPrintRouter(theEnv,WERROR,"\nhas constraint conflicts which make the pattern unmatchable.\n");
  }
