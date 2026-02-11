CheckTemplateFact(
  void *theEnv,
  struct fact *theFact)
  {
   struct field *sublist;
   int i;
   struct deftemplate *theDeftemplate;
   struct templateSlot *slotPtr;
   DATA_OBJECT theData;
   char thePlace[20];
   int rv;

   if (! EnvGetDynamicConstraintChecking(theEnv)) return;

   sublist = theFact->theProposition.theFields;


   theDeftemplate = theFact->whichDeftemplate;
   if (theDeftemplate == NULL) return;
   if (theDeftemplate->implied) return;


   i = 0;
   for (slotPtr = theDeftemplate->slotList;
        slotPtr != NULL;
        slotPtr = slotPtr->next)
     {


      if (slotPtr->multislot == FALSE)
        {
         theData.type = sublist[i].type;
         theData.value = sublist[i].value;
         i++;
        }
      else
        {
         theData.type = MULTIFIELD;
         theData.value = (void *) sublist[i].value;
         SetDOBegin(theData,1);
         SetDOEnd(theData,((struct multifield *) sublist[i].value)->multifieldLength);
         i++;
        }


      rv = ConstraintCheckDataObject(theEnv,&theData,slotPtr->constraints);
      if (rv != NO_VIOLATION)
        {
         sprintf(thePlace,"fact f-%-5ld ",theFact->factIndex);

         PrintErrorID(theEnv,"CSTRNCHK",1,TRUE);
         EnvPrintRouter(theEnv,WERROR,"Slot value ");
         PrintDataObject(theEnv,WERROR,&theData);
         EnvPrintRouter(theEnv,WERROR," ");
         ConstraintViolationErrorMessage(theEnv,NULL,thePlace,FALSE,0,slotPtr->slotName,
                                         0,rv,slotPtr->constraints,TRUE);
         SetHaltExecution(theEnv,TRUE);
         return;
        }
     }

   return;
  }
