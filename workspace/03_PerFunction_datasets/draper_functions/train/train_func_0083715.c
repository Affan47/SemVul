Function1Parse(
  void *theEnv,
  char *logicalName)
  {
   struct token theToken;
   struct expr *top;


   GetToken(theEnv,logicalName,&theToken);
   if (theToken.type != SYMBOL)
     {
      PrintErrorID(theEnv,"EXPRNPSR",1,TRUE);
      EnvPrintRouter(theEnv,WERROR,"A function name must be a symbol\n");
      return(NULL);
     }


   top = Function2Parse(theEnv,logicalName,ValueToString(theToken.value));
   return(top);
  }
