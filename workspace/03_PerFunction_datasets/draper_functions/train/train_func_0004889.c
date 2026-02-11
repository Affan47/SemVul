EnvEval(
  void *theEnv,
  char *theString,
  DATA_OBJECT_PTR returnValue)
  {
   struct expr *top;
   int ov;
   static int depth = 0;
   char logicalNameBuffer[20];
   struct BindInfo *oldBinds;


   depth++;
   sprintf(logicalNameBuffer,"Eval-%d",depth);
   if (OpenStringSource(theEnv,logicalNameBuffer,theString,0) == 0)
     {
      SetpType(returnValue,SYMBOL);
      SetpValue(returnValue,EnvFalseSymbol(theEnv));
      depth--;
      return(FALSE);
     }


   ov = GetPPBufferStatus(theEnv);
   SetPPBufferStatus(theEnv,FALSE);
   oldBinds = GetParsedBindNames(theEnv);
   SetParsedBindNames(theEnv,NULL);


   top = ParseAtomOrExpression(theEnv,logicalNameBuffer,NULL);


   SetPPBufferStatus(theEnv,ov);
   ClearParsedBindNames(theEnv);
   SetParsedBindNames(theEnv,oldBinds);


   if (top == NULL)
     {
      SetEvaluationError(theEnv,TRUE);
      CloseStringSource(theEnv,logicalNameBuffer);
      SetpType(returnValue,SYMBOL);
      SetpValue(returnValue,EnvFalseSymbol(theEnv));
      depth--;
      return(FALSE);
     }


   if ((top->type == MF_GBL_VARIABLE) || (top->type == MF_VARIABLE))
     {
      PrintErrorID(theEnv,"MISCFUN",1,FALSE);
      EnvPrintRouter(theEnv,WERROR,"expand$ must be used in the argument list of a function call.\n");
      SetEvaluationError(theEnv,TRUE);
      CloseStringSource(theEnv,logicalNameBuffer);
      SetpType(returnValue,SYMBOL);
      SetpValue(returnValue,EnvFalseSymbol(theEnv));
      ReturnExpression(theEnv,top);
      depth--;
      return(FALSE);
     }


   if (ExpressionContainsVariables(top,FALSE))
     {
      PrintErrorID(theEnv,"STRNGFUN",2,FALSE);
      EnvPrintRouter(theEnv,WERROR,"Some variables could not be accessed by the eval function.\n");
      SetEvaluationError(theEnv,TRUE);
      CloseStringSource(theEnv,logicalNameBuffer);
      SetpType(returnValue,SYMBOL);
      SetpValue(returnValue,EnvFalseSymbol(theEnv));
      ReturnExpression(theEnv,top);
      depth--;
      return(FALSE);
     }


   ExpressionInstall(theEnv,top);
   EvaluateExpression(theEnv,top,returnValue);
   ExpressionDeinstall(theEnv,top);

   depth--;
   ReturnExpression(theEnv,top);
   CloseStringSource(theEnv,logicalNameBuffer);

   if (GetEvaluationError(theEnv)) return(FALSE);
   return(TRUE);
  }
