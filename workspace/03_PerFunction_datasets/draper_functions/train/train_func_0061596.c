PropagatePatternType(
  struct lhsParseNode *theLHS,
  struct patternParser *theParser)
  {
   while (theLHS != NULL)
     {
      theLHS->patternType = theParser;
      if (theLHS->right != NULL) PropagatePatternType(theLHS->right,theParser);
      if (theLHS->expression != NULL) PropagatePatternType(theLHS->expression,theParser);
      theLHS = theLHS->bottom;
     }
  }
