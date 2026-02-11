DeallocateFactBloadData(
  void *theEnv)
  {
   unsigned long space;
   int i;

   for (i = 0; i < FactBinaryData(theEnv)->NumberOfPatterns; i++)
     { DestroyAlphaBetaMemory(theEnv,FactBinaryData(theEnv)->FactPatternArray[i].header.alphaMemory); }

   space = FactBinaryData(theEnv)->NumberOfPatterns * sizeof(struct factPatternNode);
   if (space != 0) genlongfree(theEnv,(void *) FactBinaryData(theEnv)->FactPatternArray,space);
  }
