MarkPatternForIncrementalReset(
  void *theEnv,
  int rhsType,
  struct patternNodeHeader *theHeader,
  int value)
  {
   struct patternParser *tempParser;

   tempParser = GetPatternParser(theEnv,rhsType);

   if (tempParser != NULL)
     {
      if (tempParser->markIRPatternFunction != NULL)
        { (*tempParser->markIRPatternFunction)(theEnv,theHeader,value); }
     }
  }
