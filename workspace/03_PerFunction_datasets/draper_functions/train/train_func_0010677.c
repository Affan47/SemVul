InstallInstance(
  void *theEnv,
  INSTANCE_TYPE *ins,
  int set)
  {
   if (set == TRUE)
     {
      if (ins->installed)
        return;
#if DEBUGGING_FUNCTIONS
      if (ins->cls->traceInstances)
        PrintInstanceWatch(theEnv,MAKE_TRACE,ins);
#endif
      ins->installed = 1;
      ins->depth = EvaluationData(theEnv)->CurrentEvaluationDepth;
      IncrementSymbolCount(ins->name);
      IncrementDefclassBusyCount(theEnv,(void *) ins->cls);
      InstanceData(theEnv)->GlobalNumberOfInstances++;
     }
   else
     {
      if (! ins->installed)
        return;
      ins->installed = 0;
      InstanceData(theEnv)->GlobalNumberOfInstances--;


     }
  }
