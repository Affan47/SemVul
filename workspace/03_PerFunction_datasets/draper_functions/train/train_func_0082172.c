EnvSend(
  void *theEnv,
  DATA_OBJECT *idata,
  char *msg,
  char *args,
  DATA_OBJECT *result)
  {
   int error;
   EXPRESSION *iexp;
   SYMBOL_HN *msym;

   if ((EvaluationData(theEnv)->CurrentEvaluationDepth == 0) && (! CommandLineData(theEnv)->EvaluatingTopLevelCommand) &&
       (EvaluationData(theEnv)->CurrentExpression == NULL))
     { PeriodicCleanup(theEnv,TRUE,FALSE); }

   SetEvaluationError(theEnv,FALSE);
   result->type = SYMBOL;
   result->value = EnvFalseSymbol(theEnv);
   msym = FindSymbolHN(theEnv,msg);
   if (msym == NULL)
     {
      PrintNoHandlerError(theEnv,msg);
      SetEvaluationError(theEnv,TRUE);
      return;
     }
   iexp = GenConstant(theEnv,idata->type,idata->value);
   iexp->nextArg = ParseConstantArguments(theEnv,args,&error);
   if (error == TRUE)
     {
      ReturnExpression(theEnv,iexp);
      SetEvaluationError(theEnv,TRUE);
      return;
     }
   PerformMessage(theEnv,result,iexp,msym);
   ReturnExpression(theEnv,iexp);
  }
