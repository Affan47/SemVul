CheckRangeAgainstCardinalityConstraint(
  void *theEnv,
  int min,
  int max,
  CONSTRAINT_RECORD *constraints)
  {


   if (constraints == NULL) return(TRUE);


   if (constraints->maxFields != NULL)
     {
      if (constraints->maxFields->value != SymbolData(theEnv)->PositiveInfinity)
        {
         if (min > ValueToLong(constraints->maxFields->value))
           { return(FALSE); }
        }
     }


   if ((constraints->minFields != NULL) && (max != -1))
     {
      if (constraints->minFields->value != SymbolData(theEnv)->NegativeInfinity)
        {
         if (max < ValueToLong(constraints->minFields->value))
           { return(FALSE); }
        }
     }


   return(TRUE);
  }
