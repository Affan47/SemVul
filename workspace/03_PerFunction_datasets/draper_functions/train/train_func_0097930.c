ReturnPartialMatch(
  void *theEnv,
  struct partialMatch *waste)
  {


   if (waste->busy)
     {
      waste->next = EngineData(theEnv)->GarbagePartialMatches;
      EngineData(theEnv)->GarbagePartialMatches = waste;
      return;
     }


   if (waste->betaMemory == FALSE)
     {
      if (waste->binds[0].gm.theMatch->markers != NULL)
        { ReturnMarkers(theEnv,waste->binds[0].gm.theMatch->markers); }
      rm(theEnv,waste->binds[0].gm.theMatch,(int) sizeof(struct alphaMatch));
     }


   if (waste->dependentsf) RemovePMDependencies(theEnv,waste);


   rtn_var_struct(theEnv,partialMatch,(int) sizeof(struct genericMatch *) *
                  (waste->bcount + waste->activationf + waste->dependentsf - 1),
                  waste);
  }
