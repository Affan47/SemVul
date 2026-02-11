FactSlotValue(
  void *theEnv,
  void *vTheFact,
  char *theSlotName,
  DATA_OBJECT *returnValue)
  {
   struct fact *theFact = (struct fact *) vTheFact;
   short position;


   if (theFact->whichDeftemplate->implied)
     {
      if (strcmp(theSlotName,"implied") != 0)
        {
         SetEvaluationError(theEnv,TRUE);
         InvalidDeftemplateSlotMessage(theEnv,theSlotName,
                                       ValueToString(theFact->whichDeftemplate->header.name),FALSE);
         return;
        }
     }

   else if (FindSlot(theFact->whichDeftemplate,(SYMBOL_HN *) EnvAddSymbol(theEnv,theSlotName),&position) == NULL)
     {
      SetEvaluationError(theEnv,TRUE);
      InvalidDeftemplateSlotMessage(theEnv,theSlotName,
                                    ValueToString(theFact->whichDeftemplate->header.name),FALSE);
      return;
     }


   if (theFact->whichDeftemplate->implied)
     { EnvGetFactSlot(theEnv,theFact,NULL,returnValue); }
   else
     { EnvGetFactSlot(theEnv,theFact,theSlotName,returnValue); }
  }
