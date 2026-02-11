FlushAlphaBetaMemory(
  void *theEnv,
  struct partialMatch *pfl)
  {
   struct partialMatch *pfltemp;

   while (pfl != NULL)
     {
      pfltemp = pfl->next;

      if (((pfl->notOriginf) && (pfl->counterf == FALSE)) ||
          (pfl->betaMemory == FALSE))
        {
         pfl->next = EngineData(theEnv)->GarbagePartialMatches;
         EngineData(theEnv)->GarbagePartialMatches = pfl;
        }
      else
        { ReturnPartialMatch(theEnv,pfl); }

      pfl = pfltemp;
     }
  }
