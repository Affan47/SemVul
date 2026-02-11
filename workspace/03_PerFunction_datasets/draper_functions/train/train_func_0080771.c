SetErrorCaptureValues(
  void *theEnv,
  DATA_OBJECT_PTR returnValue)
  {
   struct multifield *theMultifield;

   theMultifield = (struct multifield *) EnvCreateMultifield(theEnv,2L);

   if (ParseFunctionData(theEnv)->ErrorString != NULL)
     {
      SetMFType(theMultifield,1,STRING);
      SetMFValue(theMultifield,1,EnvAddSymbol(theEnv,ParseFunctionData(theEnv)->ErrorString));
     }
   else
     {
      SetMFType(theMultifield,1,SYMBOL);
      SetMFValue(theMultifield,1,EnvFalseSymbol(theEnv));
     }

   if (ParseFunctionData(theEnv)->WarningString != NULL)
     {
      SetMFType(theMultifield,2,STRING);
      SetMFValue(theMultifield,2,EnvAddSymbol(theEnv,ParseFunctionData(theEnv)->WarningString));
     }
   else
     {
      SetMFType(theMultifield,2,SYMBOL);
      SetMFValue(theMultifield,2,EnvFalseSymbol(theEnv));
     }

   SetpType(returnValue,MULTIFIELD);
   SetpDOBegin(returnValue,1);
   SetpDOEnd(returnValue,2);
   SetpValue(returnValue,(void *) theMultifield);
  }
