GetConstraintRecord(
  void *theEnv)
  {
   CONSTRAINT_RECORD *constraints;
   unsigned i;

   constraints = get_struct(theEnv,constraintRecord);

   for (i = 0 ; i < sizeof(CONSTRAINT_RECORD) ; i++)
     { ((char *) constraints)[i] = '\0'; }

   SetAnyAllowedFlags(constraints,TRUE);

   constraints->multifieldsAllowed = FALSE;
   constraints->singlefieldsAllowed = TRUE;

   constraints->anyRestriction = FALSE;
   constraints->symbolRestriction = FALSE;
   constraints->stringRestriction = FALSE;
   constraints->floatRestriction = FALSE;
   constraints->integerRestriction = FALSE;
   constraints->classRestriction = FALSE;
   constraints->instanceNameRestriction = FALSE;
   constraints->classList = NULL;
   constraints->restrictionList = NULL;
   constraints->minValue = GenConstant(theEnv,SYMBOL,SymbolData(theEnv)->NegativeInfinity);
   constraints->maxValue = GenConstant(theEnv,SYMBOL,SymbolData(theEnv)->PositiveInfinity);
   constraints->minFields = GenConstant(theEnv,INTEGER,SymbolData(theEnv)->Zero);
   constraints->maxFields = GenConstant(theEnv,SYMBOL,SymbolData(theEnv)->PositiveInfinity);
   constraints->bucket = -1;
   constraints->count = 0;
   constraints->multifield = NULL;
   constraints->next = NULL;

   return(constraints);
  }
