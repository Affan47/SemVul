FactPNGetVar1(
  void *theEnv,
  void *theValue,
  DATA_OBJECT_PTR returnValue)
  {
   unsigned short theField, theSlot;
   struct fact *factPtr;
   struct field *fieldPtr;
   struct multifieldMarker *marks;
   struct multifield *segmentPtr;
   int extent;
   struct factGetVarPN1Call *hack;


   hack = (struct factGetVarPN1Call *) ValueToBitMap(theValue);


   factPtr = FactData(theEnv)->CurrentPatternFact;
   marks = FactData(theEnv)->CurrentPatternMarks;


   if (hack->factAddress)
     {
      returnValue->type = FACT_ADDRESS;
      returnValue->value = (void *) factPtr;
      return(TRUE);
     }


   if (hack->allFields)
     {
      theSlot = hack->whichSlot;
      fieldPtr = &factPtr->theProposition.theFields[theSlot];
      returnValue->type = fieldPtr->type;
      returnValue->value = fieldPtr->value;
      if (returnValue->type == MULTIFIELD)
        {
         SetpDOBegin(returnValue,1);
         SetpDOEnd(returnValue,((struct multifield *) fieldPtr->value)->multifieldLength);
        }

      return(TRUE);
     }


   theField = hack->whichField;
   theSlot = hack->whichSlot;
   fieldPtr = &factPtr->theProposition.theFields[theSlot];


   extent = -1;
   theField = AdjustFieldPosition(theEnv,marks,theField,theSlot,&extent);


   if (extent != -1)
     {
      returnValue->type = MULTIFIELD;
      returnValue->value = (void *) fieldPtr->value;
      returnValue->begin = theField;
      returnValue->end = theField + extent - 1;
      return(TRUE);
     }


   segmentPtr = (struct multifield *) fieldPtr->value;
   fieldPtr = &segmentPtr->theFields[theField];

   returnValue->type = fieldPtr->type;
   returnValue->value = fieldPtr->value;

   return(TRUE);
  }
