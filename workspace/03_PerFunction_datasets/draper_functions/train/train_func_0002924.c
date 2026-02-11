GetLoopCount(
  void *theEnv)
  {
   int depth;
   LOOP_COUNTER_STACK *tmpCounter;

   depth = ValueToInteger(GetFirstArgument()->value);
   tmpCounter = ProcedureFunctionData(theEnv)->LoopCounterStack;
   while (depth > 0)
     {
      tmpCounter = tmpCounter->nxt;
      depth--;
     }
   return(tmpCounter->loopCounter);
  }
