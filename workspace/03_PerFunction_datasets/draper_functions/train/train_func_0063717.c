BsaveObjectPatterns(
  void *theEnv,
  FILE *fp)
  {
   UNLN space;
   OBJECT_ALPHA_NODE *alphaPtr;
   OBJECT_PATTERN_NODE *patternPtr;
   BSAVE_OBJECT_ALPHA_NODE dummyAlpha;
   BSAVE_OBJECT_PATTERN_NODE dummyPattern;

   space = (sizeof(BSAVE_OBJECT_ALPHA_NODE) * ObjectReteBinaryData(theEnv)->AlphaNodeCount) +
           (sizeof(BSAVE_OBJECT_PATTERN_NODE) * ObjectReteBinaryData(theEnv)->PatternNodeCount);
   GenWrite(&space,(UNLN) sizeof(UNLN),fp);


   alphaPtr = ObjectNetworkTerminalPointer(theEnv);
   while (alphaPtr != NULL)
     {
      AssignBsavePatternHeaderValues(&dummyAlpha.header,&alphaPtr->header);
      dummyAlpha.classbmp = (long) alphaPtr->classbmp->bucket;
      if (alphaPtr->slotbmp != NULL)
        dummyAlpha.slotbmp = (long) alphaPtr->slotbmp->bucket;
      else
        dummyAlpha.slotbmp = -1L;
      dummyAlpha.patternNode = BsaveObjectPatternIndex(alphaPtr->patternNode);
      dummyAlpha.nxtInGroup = BsaveObjectAlphaIndex(alphaPtr->nxtInGroup);
      dummyAlpha.nxtTerminal = BsaveObjectAlphaIndex(alphaPtr->nxtTerminal);
      GenWrite(&dummyAlpha,(UNLN) sizeof(BSAVE_OBJECT_ALPHA_NODE),fp);
      alphaPtr = alphaPtr->nxtTerminal;
     }


   patternPtr = ObjectNetworkPointer(theEnv);
   while (patternPtr != NULL)
     {
      dummyPattern.multifieldNode = patternPtr->multifieldNode;
      dummyPattern.whichField = patternPtr->whichField;
      dummyPattern.leaveFields = patternPtr->leaveFields;
      dummyPattern.endSlot = patternPtr->endSlot;
      dummyPattern.slotNameID = patternPtr->slotNameID;
      dummyPattern.networkTest = HashedExpressionIndex(theEnv,patternPtr->networkTest);
      dummyPattern.nextLevel = BsaveObjectPatternIndex(patternPtr->nextLevel);
      dummyPattern.lastLevel = BsaveObjectPatternIndex(patternPtr->lastLevel);
      dummyPattern.leftNode = BsaveObjectPatternIndex(patternPtr->leftNode);
      dummyPattern.rightNode = BsaveObjectPatternIndex(patternPtr->rightNode);
      dummyPattern.alphaNode = BsaveObjectAlphaIndex(patternPtr->alphaNode);
      GenWrite(&dummyPattern,(UNLN) sizeof(BSAVE_OBJECT_PATTERN_NODE),fp);

      if (patternPtr->nextLevel == NULL)
        {
         while (patternPtr->rightNode == NULL)
           {
            patternPtr = patternPtr->lastLevel;
            if (patternPtr == NULL)
              {
               RestoreBloadCount(theEnv,&ObjectReteBinaryData(theEnv)->AlphaNodeCount);
               RestoreBloadCount(theEnv,&ObjectReteBinaryData(theEnv)->PatternNodeCount);
               return;
              }
           }
         patternPtr = patternPtr->rightNode;
        }
      else
        patternPtr = patternPtr->nextLevel;
     }

   RestoreBloadCount(theEnv,&ObjectReteBinaryData(theEnv)->AlphaNodeCount);
   RestoreBloadCount(theEnv,&ObjectReteBinaryData(theEnv)->PatternNodeCount);
  }
