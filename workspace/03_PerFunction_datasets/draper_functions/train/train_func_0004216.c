EnvRtnLexeme(
  void *theEnv,
  int argumentPosition)
  {
   int count = 1;
   DATA_OBJECT result;
   struct expr *argPtr;


   for (argPtr = EvaluationData(theEnv)->CurrentExpression->argList;
        (argPtr != NULL) && (count < argumentPosition);
        argPtr = argPtr->nextArg)
     { count++; }

   if (argPtr == NULL)
     {
      NonexistantError(theEnv,"RtnLexeme",
                       ValueToString(ExpressionFunctionCallName(EvaluationData(theEnv)->CurrentExpression)),
                       argumentPosition);
      SetHaltExecution(theEnv,TRUE);
      SetEvaluationError(theEnv,TRUE);
      return(NULL);
     }


   EvaluateExpression(theEnv,argPtr,&result);

   if ((result.type == SYMBOL) ||
#if OBJECT_SYSTEM
       (result.type == INSTANCE_NAME) ||
#endif
       (result.type == STRING))
     { return(ValueToString(result.value));}


   ExpectedTypeError3(theEnv,"RtnLexeme",
                  ValueToString(ExpressionFunctionCallName(EvaluationData(theEnv)->CurrentExpression)),
                  argumentPosition,"symbol, string, or instance name");
   SetHaltExecution(theEnv,TRUE);
   SetEvaluationError(theEnv,TRUE);
   return(NULL);
  }
