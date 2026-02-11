InstanceNameCommand(
  void *theEnv,
  DATA_OBJECT *result)
  {
   INSTANCE_TYPE *ins;
   DATA_OBJECT temp;

   result->type = SYMBOL;
   result->value = EnvFalseSymbol(theEnv);
   if (EnvArgTypeCheck(theEnv,"instance-name",1,INSTANCE_OR_INSTANCE_NAME,&temp) == FALSE)
     return;
   if (temp.type == INSTANCE_ADDRESS)
     {
      ins = (INSTANCE_TYPE *) temp.value;
      if (ins->garbage == 1)
        {
         StaleInstanceAddress(theEnv,"instance-name",0);
         SetEvaluationError(theEnv,TRUE);
         return;
        }
     }
   else
     {
      ins = FindInstanceBySymbol(theEnv,(SYMBOL_HN *) temp.value);
      if (ins == NULL)
        {
         NoInstanceError(theEnv,ValueToString(temp.value),"instance-name");
         return;
        }
     }
   result->type = INSTANCE_NAME;
   result->value = (void *) ins->name;
  }
