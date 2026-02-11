ClearBloadGenerics(
  void *theEnv)
  {
   register long i;
   unsigned long space;

   space = (unsigned long) (sizeof(DEFGENERIC_MODULE) * DefgenericBinaryData(theEnv)->ModuleCount);
   if (space == 0L)
     return;
   genlongfree(theEnv,(void *) DefgenericBinaryData(theEnv)->ModuleArray,space);
   DefgenericBinaryData(theEnv)->ModuleArray = NULL;
   DefgenericBinaryData(theEnv)->ModuleCount = 0L;

   for (i = 0 ; i < DefgenericBinaryData(theEnv)->GenericCount ; i++)
     UnmarkConstructHeader(theEnv,&DefgenericBinaryData(theEnv)->DefgenericArray[i].header);

   space = (unsigned long) (sizeof(DEFGENERIC) * DefgenericBinaryData(theEnv)->GenericCount);
   if (space == 0L)
     return;
   genlongfree(theEnv,(void *) DefgenericBinaryData(theEnv)->DefgenericArray,space);
   DefgenericBinaryData(theEnv)->DefgenericArray = NULL;
   DefgenericBinaryData(theEnv)->GenericCount = 0L;

   space = (unsigned long) (sizeof(DEFMETHOD) * DefgenericBinaryData(theEnv)->MethodCount);
   if (space == 0L)
     return;
   genlongfree(theEnv,(void *) DefgenericBinaryData(theEnv)->MethodArray,space);
   DefgenericBinaryData(theEnv)->MethodArray = NULL;
   DefgenericBinaryData(theEnv)->MethodCount = 0L;

   space = (unsigned long) (sizeof(RESTRICTION) * DefgenericBinaryData(theEnv)->RestrictionCount);
   if (space == 0L)
     return;
   genlongfree(theEnv,(void *) DefgenericBinaryData(theEnv)->RestrictionArray,space);
   DefgenericBinaryData(theEnv)->RestrictionArray = NULL;
   DefgenericBinaryData(theEnv)->RestrictionCount = 0L;

#if ! OBJECT_SYSTEM
   for (i = 0 ; i < DefgenericBinaryData(theEnv)->TypeCount ; i++)
     DecrementIntegerCount(theEnv,(INTEGER_HN *) DefgenericBinaryData(theEnv)->TypeArray[i]);
#endif
   space = (unsigned long) (sizeof(void *) * DefgenericBinaryData(theEnv)->TypeCount);
   if (space == 0L)
     return;
   genlongfree(theEnv,(void *) DefgenericBinaryData(theEnv)->TypeArray,space);
   DefgenericBinaryData(theEnv)->TypeArray = NULL;
   DefgenericBinaryData(theEnv)->TypeCount = 0L;
  }
