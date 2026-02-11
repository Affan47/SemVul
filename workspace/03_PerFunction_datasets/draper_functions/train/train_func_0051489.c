InitializeClasses(
  void *theEnv)
  {
   register int i;

   DefclassData(theEnv)->ClassTable =
      (DEFCLASS **) gm2(theEnv,(int) (sizeof(DEFCLASS *) * CLASS_TABLE_HASH_SIZE));
   for (i = 0 ; i < CLASS_TABLE_HASH_SIZE ; i++)
     DefclassData(theEnv)->ClassTable[i] = NULL;
   DefclassData(theEnv)->SlotNameTable =
      (SLOT_NAME **) gm2(theEnv,(int) (sizeof(SLOT_NAME *) * SLOT_NAME_TABLE_HASH_SIZE));
   for (i = 0 ; i < SLOT_NAME_TABLE_HASH_SIZE ; i++)
     DefclassData(theEnv)->SlotNameTable[i] = NULL;
  }
