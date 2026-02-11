TestForFirstInstanceInClass(
  void *theEnv,
  struct defmodule *theModule,
  int id,
  DEFCLASS *cls,
  QUERY_CLASS *qchain,
  int indx)
  {
   register unsigned i;
   INSTANCE_TYPE *ins;
   DATA_OBJECT temp;

   if (TestTraversalID(cls->traversalRecord,id))
     return(FALSE);
   SetTraversalID(cls->traversalRecord,id);
   if (DefclassInScope(theEnv,cls,theModule) == FALSE)
     return(FALSE);
   ins = cls->instanceList;
   while (ins != NULL)
     {
      InstanceQueryData(theEnv)->QueryCore->solns[indx] = ins;
      if (qchain->nxt != NULL)
        {
         ins->busy++;
         if (TestForFirstInChain(theEnv,qchain->nxt,indx+1) == TRUE)
           {
            ins->busy--;
            break;
           }
         ins->busy--;
         if ((EvaluationData(theEnv)->HaltExecution == TRUE) || (InstanceQueryData(theEnv)->AbortQuery == TRUE))
           break;
        }
      else
        {
         ins->busy++;
         EvaluationData(theEnv)->CurrentEvaluationDepth++;
         EvaluateExpression(theEnv,InstanceQueryData(theEnv)->QueryCore->query,&temp);
         EvaluationData(theEnv)->CurrentEvaluationDepth--;
         PeriodicCleanup(theEnv,FALSE,TRUE);
         ins->busy--;
         if (EvaluationData(theEnv)->HaltExecution == TRUE)
           break;
         if ((temp.type != SYMBOL) ? TRUE :
             (temp.value != EnvFalseSymbol(theEnv)))
           break;
        }
      ins = ins->nxtClass;
      while ((ins != NULL) ? (ins->garbage == 1) : FALSE)
        ins = ins->nxtClass;
     }
   if (ins != NULL)
     return(((EvaluationData(theEnv)->HaltExecution == TRUE) || (InstanceQueryData(theEnv)->AbortQuery == TRUE))
             ? FALSE : TRUE);
   for (i = 0 ; i < cls->directSubclasses.classCount ; i++)
     {
      if (TestForFirstInstanceInClass(theEnv,theModule,id,cls->directSubclasses.classArray[i],
                                      qchain,indx))
        return(TRUE);
      if ((EvaluationData(theEnv)->HaltExecution == TRUE) || (InstanceQueryData(theEnv)->AbortQuery == TRUE))
        return(FALSE);
     }
   return(FALSE);
  }
