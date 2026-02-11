PrintTemplateFact(
  void *theEnv,
  char *logicalName,
  struct fact *theFact,
  int seperateLines,
  int ignoreDefaults)
  {
   struct field *sublist;
   int i;
   struct deftemplate *theDeftemplate;
   struct templateSlot *slotPtr;
   DATA_OBJECT tempDO;
   int slotPrinted = FALSE;


   theDeftemplate = theFact->whichDeftemplate;
   sublist = theFact->theProposition.theFields;


   EnvPrintRouter(theEnv,logicalName,"(");
   EnvPrintRouter(theEnv,logicalName,theDeftemplate->header.name->contents);


   slotPtr = theDeftemplate->slotList;

   i = 0;
   while (slotPtr != NULL)
     {


      if (ignoreDefaults && (slotPtr->defaultDynamic == FALSE))
        {
         DeftemplateSlotDefault(theEnv,theDeftemplate,slotPtr,&tempDO,TRUE);

         if (slotPtr->multislot == FALSE)
           {
            if ((GetType(tempDO) == sublist[i].type) &&
                (GetValue(tempDO) == sublist[i].value))
              {
               i++;
               slotPtr = slotPtr->next;
               continue;
              }
           }
         else if (MultifieldsEqual((struct multifield*) GetValue(tempDO),
                                   (struct multifield *) sublist[i].value))
           {
            i++;
            slotPtr = slotPtr->next;
            continue;
           }
        }


      if (! slotPrinted)
        {
         slotPrinted = TRUE;
         EnvPrintRouter(theEnv,logicalName," ");
        }

      if (seperateLines)
        { EnvPrintRouter(theEnv,logicalName,"\n   "); }

      EnvPrintRouter(theEnv,logicalName,"(");
      EnvPrintRouter(theEnv,logicalName,slotPtr->slotName->contents);


      if (slotPtr->multislot == FALSE)
        {
         EnvPrintRouter(theEnv,logicalName," ");
         PrintAtom(theEnv,logicalName,sublist[i].type,sublist[i].value);
        }


      else
        {
         struct multifield *theSegment;

         theSegment = (struct multifield *) sublist[i].value;
         if (theSegment->multifieldLength > 0)
           {
            EnvPrintRouter(theEnv,logicalName," ");
            PrintMultifield(theEnv,logicalName,(struct multifield *) sublist[i].value,
                            0,(long) theSegment->multifieldLength-1,FALSE);
           }
        }


      i++;
      EnvPrintRouter(theEnv,logicalName,")");
      slotPtr = slotPtr->next;
      if (slotPtr != NULL) EnvPrintRouter(theEnv,logicalName," ");
     }

   EnvPrintRouter(theEnv,logicalName,")");
  }
