CallSpecificMethod(
  void *theEnv,
  DATA_OBJECT *result)
  {
   DATA_OBJECT temp;
   DEFGENERIC *gfunc;
   int mi;

   result->type = SYMBOL;
   result->value = EnvFalseSymbol(theEnv);
   if (EnvArgTypeCheck(theEnv,"call-specific-method",1,SYMBOL,&temp) == FALSE)
     return;
   gfunc = CheckGenericExists(theEnv,"call-specific-method",DOToString(temp));
   if (gfunc == NULL)
     return;
   if (EnvArgTypeCheck(theEnv,"call-specific-method",2,INTEGER,&temp) == FALSE)
     return;
   mi = CheckMethodExists(theEnv,"call-specific-method",gfunc,DOToInteger(temp));
   if (mi == -1)
     return;
   gfunc->methods[mi].busy++;
   GenericDispatch(theEnv,gfunc,NULL,&gfunc->methods[mi],
                   GetFirstArgument()->nextArg->nextArg,result);
   gfunc->methods[mi].busy--;
  }
