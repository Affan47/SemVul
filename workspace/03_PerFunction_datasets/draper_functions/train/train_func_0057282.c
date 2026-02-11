FetchCommand(
  void *theEnv,
  DATA_OBJECT *result)
  {
   int load_ct;
   DATA_OBJECT arg_ptr;

   result->type = SYMBOL;
   result->value = EnvFalseSymbol(theEnv);
   if (EnvArgTypeCheck(theEnv,"fetch",1,SYMBOL_OR_STRING,&arg_ptr) == FALSE)
      return;
   load_ct = TextLookupFetch(theEnv,DOToString(arg_ptr));
   if (load_ct <= 0)
     {
      if (load_ct == 0)
        {
         PrintErrorID(theEnv,"TEXTPRO",3,FALSE);
         EnvPrintRouter(theEnv,WERROR,"No entries found.\n");
        }

      return;
     }
   result->type = INTEGER;
   result->value = (void *) EnvAddLong(theEnv,(long) load_ct);
  }
