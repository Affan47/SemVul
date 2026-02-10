FindDefaultValue(
  void *theEnv,
  int theType,
  CONSTRAINT_RECORD *theConstraints,
  void *standardDefault)
  {
   struct expr *theList;


   theList = theConstraints->restrictionList;
   while (theList != NULL)
     {
      if (theList->type == theType) return(theList->value);
      theList = theList->nextArg;
     }


   if (theType == INTEGER)
     {
      if (theConstraints->minValue->type == INTEGER)
        { return(theConstraints->minValue->value); }
      else if (theConstraints->minValue->type == FLOAT)
        { return(EnvAddLong(theEnv,(long) ValueToDouble(theConstraints->minValue->value))); }
      else if (theConstraints->maxValue->type == INTEGER)
        { return(theConstraints->maxValue->value); }
      else if (theConstraints->maxValue->type == FLOAT)
        { return(EnvAddLong(theEnv,(long) ValueToDouble(theConstraints->maxValue->value))); }
     }
   else if (theType == FLOAT)
     {
      if (theConstraints->minValue->type == FLOAT)
        { return(theConstraints->minValue->value); }
      else if (theConstraints->minValue->type == INTEGER)
        { return(EnvAddDouble(theEnv,(double) ValueToLong(theConstraints->minValue->value))); }
      else if (theConstraints->maxValue->type == FLOAT)
        { return(theConstraints->maxValue->value); }
      else if (theConstraints->maxValue->type == INTEGER)
        { return(EnvAddDouble(theEnv,(double) ValueToLong(theConstraints->maxValue->value))); }
     }


   return(standardDefault);
  }
