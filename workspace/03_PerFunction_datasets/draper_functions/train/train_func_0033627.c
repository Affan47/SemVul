DestroyFactPatternNetwork(
  void *theEnv,
  struct factPatternNode *thePattern)
  {
   struct factPatternNode *patternPtr;

   if (thePattern == NULL) return;

   while (thePattern != NULL)
     {
      patternPtr = thePattern->rightNode;

      DestroyFactPatternNetwork(theEnv,thePattern->nextLevel);

      DestroyAlphaBetaMemory(theEnv,thePattern->header.alphaMemory);

#if (! BLOAD_ONLY) && (! RUN_TIME)
      rtn_struct(theEnv,factPatternNode,thePattern);
#endif

      thePattern = patternPtr;
     }
  }
