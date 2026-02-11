InstancePCommand(
  void *theEnv)
  {
   DATA_OBJECT temp;

   EvaluateExpression(theEnv,GetFirstArgument(),&temp);
   if ((GetType(temp) == INSTANCE_NAME) || (GetType(temp) == INSTANCE_ADDRESS))
     return(TRUE);
   return(FALSE);
  }
