DestroyObjectPatternNetwork(
  void *theEnv,
  OBJECT_PATTERN_NODE *thePattern)
  {
   OBJECT_PATTERN_NODE *patternPtr;

   if (thePattern == NULL) return;

   while (thePattern != NULL)
     {
      patternPtr = thePattern->rightNode;

      DestroyObjectPatternNetwork(theEnv,thePattern->nextLevel);
      DestroyObjectAlphaNodes(theEnv,thePattern->alphaNode);
#if ! RUN_TIME
      rtn_struct(theEnv,objectPatternNode,thePattern);
#endif
      thePattern = patternPtr;
     }
  }
