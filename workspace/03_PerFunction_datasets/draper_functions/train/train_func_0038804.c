ResetDefinstancesAction(
  void *theEnv,
  struct constructHeader *vDefinstances,
  void *userBuffer)
  {
#if MAC_MCW || IBM_MCW || MAC_XCD
#pragma unused(userBuffer)
#endif
   DEFINSTANCES *theDefinstances = (DEFINSTANCES *) vDefinstances;
   EXPRESSION *theExp;
   DATA_OBJECT temp;

   SaveCurrentModule(theEnv);
   EnvSetCurrentModule(theEnv,(void *) vDefinstances->whichModule->theModule);
   theDefinstances->busy++;
   for (theExp = theDefinstances->mkinstance ;
        theExp != NULL ;
        theExp = GetNextArgument(theExp))
     {
      EvaluateExpression(theEnv,theExp,&temp);
      if (EvaluationData(theEnv)->HaltExecution ||
          ((GetType(temp) == SYMBOL) &&
           (GetValue(temp) == EnvFalseSymbol(theEnv))))
        {
         RestoreCurrentModule(theEnv);
         theDefinstances->busy--;
         return;
        }
     }
   theDefinstances->busy--;
   RestoreCurrentModule(theEnv);
  }
