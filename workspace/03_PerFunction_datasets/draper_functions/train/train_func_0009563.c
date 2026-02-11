EnvSlotCardinality(
  void *theEnv,
  void *clsptr,
  char *sname,
  DATA_OBJECT *result)
  {
   register SLOT_DESC *sp;

   if ((sp = SlotInfoSlot(theEnv,result,(DEFCLASS *) clsptr,sname,"slot-cardinality")) == NULL)
     return;
   if (sp->multiple == 0)
     {
      EnvSetMultifieldErrorValue(theEnv,result);
      return;
     }
   result->end = 1;
   result->value = EnvCreateMultifield(theEnv,2L);
   if (sp->constraint != NULL)
     {
      SetMFType(result->value,1,sp->constraint->minFields->type);
      SetMFValue(result->value,1,sp->constraint->minFields->value);
      SetMFType(result->value,2,sp->constraint->maxFields->type);
      SetMFValue(result->value,2,sp->constraint->maxFields->value);
     }
   else
     {
      SetMFType(result->value,1,INTEGER);
      SetMFValue(result->value,1,SymbolData(theEnv)->Zero);
      SetMFType(result->value,2,SYMBOL);
      SetMFValue(result->value,2,SymbolData(theEnv)->PositiveInfinity);
     }
  }
