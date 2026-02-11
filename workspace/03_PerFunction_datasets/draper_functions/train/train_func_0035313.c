DestroyDefglobal(
  void *theEnv,
  void *vTheDefglobal)
  {
#if (MAC_MCW || IBM_MCW) && BLOAD_ONLY
#pragma unused(theEnv,vTheDefglobal)
#endif

#if (! BLOAD_ONLY)
   struct defglobal *theDefglobal = (struct defglobal *) vTheDefglobal;

   if (theDefglobal == NULL) return;


   if (theDefglobal->current.type == MULTIFIELD)
     { ReturnMultifield(theEnv,(struct multifield *) theDefglobal->current.value); }

#if (! RUN_TIME)


   DeinstallConstructHeader(theEnv,&theDefglobal->header);


   rtn_struct(theEnv,defglobal,theDefglobal);
#endif
#endif
  }
