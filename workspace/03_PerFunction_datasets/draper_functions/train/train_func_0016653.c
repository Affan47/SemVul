GetObjectValueGeneral(
  void *theEnv,
  DATA_OBJECT *result,
  INSTANCE_TYPE *theInstance,
  struct multifieldMarker *theMarks,
  struct ObjectMatchVar1 *matchVar)
  {
   long field, extent;
   INSTANCE_SLOT **insSlot,*basisSlot;

   if (matchVar->objectAddress)
     {
      result->type = INSTANCE_ADDRESS;
      result->value = (void *) theInstance;
      return;
     }
   if (matchVar->whichSlot == ISA_ID)
     {
      result->type = SYMBOL;
      result->value = (void *) GetDefclassNamePointer((void *) theInstance->cls);
      return;
     }
   if (matchVar->whichSlot == NAME_ID)
     {
      result->type = INSTANCE_NAME;
      result->value = (void *) theInstance->name;
      return;
     }
   insSlot =
     &theInstance->slotAddresses
     [theInstance->cls->slotNameMap[matchVar->whichSlot] - 1];


   if ((theInstance->basisSlots != NULL) &&
       (! EngineData(theEnv)->JoinOperationInProgress))
     {
      basisSlot = theInstance->basisSlots + (insSlot - theInstance->slotAddresses);
      if (basisSlot->value != NULL)
        insSlot = &basisSlot;
     }


   if (matchVar->allFields)
     {
      result->type = (unsigned short) (*insSlot)->type;
      result->value = (*insSlot)->value;
      if (result->type == MULTIFIELD)
        {
         result->begin = 0;
         SetpDOEnd(result,GetMFLength((*insSlot)->value));
        }
      return;
     }


   field = CalculateSlotField(theMarks,*insSlot,matchVar->whichField,&extent);
   if (extent == -1)
     {
      if ((*insSlot)->desc->multiple)
        {
         result->type = GetMFType((*insSlot)->value,field);
         result->value = GetMFValue((*insSlot)->value,field);
        }
      else
        {
         result->type = (unsigned short) (*insSlot)->type;
         result->value = (*insSlot)->value;
        }
     }
   else
     {
      result->type = MULTIFIELD;
      result->value = (*insSlot)->value;
      result->begin = field - 1;
      result->end = field + extent - 2;
     }
  }
