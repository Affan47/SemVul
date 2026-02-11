EnvPutFactSlot(
  void *theEnv,
  void *vTheFact,
  char *slotName,
  DATA_OBJECT *theValue)
  {
   struct fact *theFact = (struct fact *) vTheFact;
   struct deftemplate *theDeftemplate;
   struct templateSlot *theSlot;
   short whichSlot;


   theDeftemplate = theFact->whichDeftemplate;


   if (theDeftemplate->implied)
     {
      if ((slotName != NULL) || (theValue->type != MULTIFIELD))
        { return(FALSE); }

      if (theFact->theProposition.theFields[0].type == MULTIFIELD)
        { ReturnMultifield(theEnv,(struct multifield *) theFact->theProposition.theFields[0].value); }

      theFact->theProposition.theFields[0].type = theValue->type;
      theFact->theProposition.theFields[0].value = DOToMultifield(theEnv,theValue);

      return(TRUE);
     }


   if ((theSlot = FindSlot(theDeftemplate,(SYMBOL_HN *) EnvAddSymbol(theEnv,slotName),&whichSlot)) == NULL)
     { return(FALSE); }


   if (((theSlot->multislot == 0) && (theValue->type == MULTIFIELD)) ||
       ((theSlot->multislot == 1) && (theValue->type != MULTIFIELD)))
     { return(FALSE); }


   if (theFact->theProposition.theFields[whichSlot-1].type == MULTIFIELD)
     { ReturnMultifield(theEnv,(struct multifield *) theFact->theProposition.theFields[whichSlot-1].value); }

   theFact->theProposition.theFields[whichSlot-1].type = theValue->type;

   if (theValue->type == MULTIFIELD)
     { theFact->theProposition.theFields[whichSlot-1].value = DOToMultifield(theEnv,theValue); }
   else
     { theFact->theProposition.theFields[whichSlot-1].value = theValue->value; }

   return(TRUE);
  }
