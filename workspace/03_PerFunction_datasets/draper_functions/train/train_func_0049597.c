FactGetVarPN1(
  void *theEnv,
  struct lhsParseNode *theNode)
  {
   struct factGetVarPN1Call hack;


   ClearBitString(&hack,sizeof(struct factGetVarPN1Call));


   if (theNode->slotNumber <= 0)
     {
      hack.factAddress = 1;
      hack.allFields = 0;
      hack.whichSlot = 0;
      hack.whichField = 0;
     }


   else if (theNode->index <= 0)
     {
      hack.factAddress = 0;
      hack.allFields = 1;
      hack.whichSlot = (unsigned short) (theNode->slotNumber - 1);
      hack.whichField = 0;
     }


   else
     {
      hack.factAddress = 0;
      hack.allFields = 0;
      hack.whichSlot = (unsigned short) (theNode->slotNumber - 1);
      hack.whichField = (unsigned short) (theNode->index - 1);
     }


   return(AddBitMap(theEnv,&hack,sizeof(struct factGetVarPN1Call)));
  }
