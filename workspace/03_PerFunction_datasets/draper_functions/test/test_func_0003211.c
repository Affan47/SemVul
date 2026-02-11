ClearDefinstancesBload(
  void *theEnv)
  {
   register long i;
   unsigned long space;

   space = (unsigned long) (sizeof(DEFINSTANCES_MODULE) * DefinstancesBinaryData(theEnv)->ModuleCount);
   if (space == 0L)
     return;
   genlongfree(theEnv,(void *) DefinstancesBinaryData(theEnv)->ModuleArray,space);
   DefinstancesBinaryData(theEnv)->ModuleArray = NULL;
   DefinstancesBinaryData(theEnv)->ModuleCount = 0L;

   for (i = 0L ; i < DefinstancesBinaryData(theEnv)->DefinstancesCount ; i++)
     UnmarkConstructHeader(theEnv,&DefinstancesBinaryData(theEnv)->DefinstancesArray[i].header);
   space = (unsigned long) (sizeof(DEFINSTANCES) * DefinstancesBinaryData(theEnv)->DefinstancesCount);
   if (space == 0L)
     return;
   genlongfree(theEnv,(void *) DefinstancesBinaryData(theEnv)->DefinstancesArray,space);
   DefinstancesBinaryData(theEnv)->DefinstancesArray = NULL;
   DefinstancesBinaryData(theEnv)->DefinstancesCount = 0L;
  }
