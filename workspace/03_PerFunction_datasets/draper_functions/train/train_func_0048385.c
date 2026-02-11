ExpressionInstall(
  void *theEnv,
  struct expr *expression)
  {
   if (expression == NULL) return;

   while (expression != NULL)
     {
      AtomInstall(theEnv,expression->type,expression->value);
      ExpressionInstall(theEnv,expression->argList);
      expression = expression->nextArg;
     }
  }
