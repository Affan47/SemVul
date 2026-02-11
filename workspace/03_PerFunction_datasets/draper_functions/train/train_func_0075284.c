ReturnFunction(
  void *theEnv,
  DATA_OBJECT_PTR result)
  {
   if (EnvRtnArgCount(theEnv) == 0)
     {
      result->type = RVOID;
      result->value = EnvFalseSymbol(theEnv);
     }
   else
     EnvRtnUnknown(theEnv,1,result);
   ProcedureFunctionData(theEnv)->ReturnFlag = TRUE;
  }
