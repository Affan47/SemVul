PosEntryRetract(
  void *theEnv,
  struct joinNode *join,
  struct alphaMatch *theAlphaNode,
  struct partialMatch *theMatch,
  int position,
  void *duringRetract)
  {
   struct partialMatch *deletedMatches;
   struct joinNode *joinPtr;
   struct partialMatch *theLast;

   while (join != NULL)
     {


      if (join->beta == NULL) return;

      join->beta = RemovePartialMatches(theEnv,theAlphaNode,join->beta,&deletedMatches,
                                        position,&theLast);


      if (deletedMatches == NULL) return;


      joinPtr = join->nextLevel;
      if (joinPtr == NULL)
        {
         DeletePartialMatches(theEnv,deletedMatches,1);
         return;
        }

      if (((struct joinNode *) (joinPtr->rightSideEntryStructure)) == join)
        {
         theMatch = deletedMatches;
         while (theMatch != NULL)
           {
            NegEntryRetract(theEnv,joinPtr,theMatch,duringRetract);
            theMatch = theMatch->next;
           }

         DeletePartialMatches(theEnv,deletedMatches,1);
         return;
        }

      DeletePartialMatches(theEnv,deletedMatches,1);
      while (joinPtr->rightDriveNode != NULL)
        {
         PosEntryRetract(theEnv,joinPtr,theAlphaNode,theMatch,position,duringRetract);
         joinPtr = joinPtr->rightDriveNode;
        }

      join = joinPtr;
     }
  }
