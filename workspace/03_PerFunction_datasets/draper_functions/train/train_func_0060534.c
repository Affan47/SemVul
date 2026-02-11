DetachFactPattern(
  void *theEnv,
  struct patternNodeHeader *thePattern)
  {
   struct factPatternNode *patternPtr;
   struct factPatternNode *upperLevel;


   patternPtr = (struct factPatternNode *) thePattern;
   ClearPatternMatches(theEnv,patternPtr);


   if (patternPtr->header.entryJoin == NULL) patternPtr->header.stopNode = FALSE;
   if (patternPtr->nextLevel != NULL) return;


   upperLevel = patternPtr;
   while (upperLevel != NULL)
     {
      if ((upperLevel->leftNode == NULL) &&
          (upperLevel->rightNode == NULL))
        {


         patternPtr = upperLevel;
         upperLevel = patternPtr->lastLevel;

         if (upperLevel == NULL)
           { FindAndSetDeftemplatePatternNetwork(theEnv,patternPtr,NULL); }
         else
           {
            upperLevel->nextLevel = NULL;
            if (upperLevel->header.stopNode) upperLevel = NULL;
           }

         RemoveHashedExpression(theEnv,patternPtr->networkTest);
         rtn_struct(theEnv,factPatternNode,patternPtr);
        }
      else if (upperLevel->leftNode != NULL)
        {


         patternPtr = upperLevel;
         upperLevel->leftNode->rightNode = upperLevel->rightNode;
         if (upperLevel->rightNode != NULL)
           { upperLevel->rightNode->leftNode = upperLevel->leftNode; }

         RemoveHashedExpression(theEnv,patternPtr->networkTest);
         rtn_struct(theEnv,factPatternNode,patternPtr);
         upperLevel = NULL;
        }
      else
        {


         patternPtr = upperLevel;
         upperLevel = upperLevel->lastLevel;
         if (upperLevel == NULL)
           { FindAndSetDeftemplatePatternNetwork(theEnv,patternPtr,patternPtr->rightNode); }
         else
           { upperLevel->nextLevel = patternPtr->rightNode; }
         patternPtr->rightNode->leftNode = NULL;

         RemoveHashedExpression(theEnv,patternPtr->networkTest);
         rtn_struct(theEnv,factPatternNode,patternPtr);
         upperLevel = NULL;
        }
     }
  }
