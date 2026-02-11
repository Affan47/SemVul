combineGroup
      (
         Int aCountNeeded,
         CSAGrpHeaderPtr aCntrlGroup
      )
   {
      CSAGrpHeaderPtr   aGrp( aCntrlGroup );
      CSAGrpHeaderPtr   aGrpBegin( NULLPTR );
      Int               aMax( theBase->currentGrps );

      for( Int x = 0; x < aMax; )
      {
         if( aCntrlGroup->groupInfo == -1 )
         {


            if( aGrpBegin == NULLPTR )
            {
               aGrpBegin = aCntrlGroup;
               ++x;
            }


            else
            {
               aGrpBegin->groupSemCount +=
                  (aCntrlGroup->groupSemCount + 1);


               aCntrlGroup->groupInfo =
                  aCntrlGroup->groupShares = aCntrlGroup->groupSemCount = 0;

               --aMax;
               theBase->currentGrps -= 1;
               theBase->currentUsed += 1;
               aCntrlGroup = aGrpBegin;
            }
         }
         else
         {
            aGrpBegin = NULLPTR;
            ++x;
         }
         aCntrlGroup += aCntrlGroup->groupSemCount+1;
      }

      return this->subsetGroup(aCountNeeded,aGrp);
   }
