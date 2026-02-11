UpdateJoin(
  void *theEnv,
  void *buf,
  long obji)
  {
   struct bsaveJoinNode *bj;

   bj = (struct bsaveJoinNode *) buf;
   DefruleBinaryData(theEnv)->JoinArray[obji].firstJoin = bj->firstJoin;
   DefruleBinaryData(theEnv)->JoinArray[obji].logicalJoin = bj->logicalJoin;
   DefruleBinaryData(theEnv)->JoinArray[obji].joinFromTheRight = bj->joinFromTheRight;
   DefruleBinaryData(theEnv)->JoinArray[obji].patternIsNegated = bj->patternIsNegated;
   DefruleBinaryData(theEnv)->JoinArray[obji].depth = bj->depth;
   DefruleBinaryData(theEnv)->JoinArray[obji].rhsType = bj->rhsType;
   DefruleBinaryData(theEnv)->JoinArray[obji].networkTest = HashedExpressionPointer(bj->networkTest);
   DefruleBinaryData(theEnv)->JoinArray[obji].nextLevel = BloadJoinPointer(bj->nextLevel);
   DefruleBinaryData(theEnv)->JoinArray[obji].lastLevel = BloadJoinPointer(bj->lastLevel);

   if (bj->joinFromTheRight == TRUE)
     { DefruleBinaryData(theEnv)->JoinArray[obji].rightSideEntryStructure =  (void *) BloadJoinPointer(bj->rightSideEntryStructure); }

   DefruleBinaryData(theEnv)->JoinArray[obji].rightMatchNode = BloadJoinPointer(bj->rightMatchNode);
   DefruleBinaryData(theEnv)->JoinArray[obji].rightDriveNode = BloadJoinPointer(bj->rightDriveNode);
   DefruleBinaryData(theEnv)->JoinArray[obji].ruleToActivate = BloadDefrulePointer(DefruleBinaryData(theEnv)->DefruleArray,bj->ruleToActivate);
   DefruleBinaryData(theEnv)->JoinArray[obji].initialize = 0;
   DefruleBinaryData(theEnv)->JoinArray[obji].marked = 0;
   DefruleBinaryData(theEnv)->JoinArray[obji].bsaveID = 0L;
   DefruleBinaryData(theEnv)->JoinArray[obji].beta = NULL;
  }
