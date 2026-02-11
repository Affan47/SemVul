AddClass(
  void *theEnv,
  DEFCLASS *cls)
  {
   DEFCLASS *ctmp;
#if DEBUGGING_FUNCTIONS
   int oldTraceInstances = FALSE,
       oldTraceSlots = FALSE;
#endif


   cls->hashTableIndex = HashClass(GetDefclassNamePointer((void *) cls));
   ctmp = (DEFCLASS *) EnvFindDefclass(theEnv,EnvGetDefclassName(theEnv,(void *) cls));

   if (ctmp != NULL)
     {
#if DEBUGGING_FUNCTIONS
      oldTraceInstances = ctmp->traceInstances;
      oldTraceSlots = ctmp->traceSlots;
#endif
      DeleteClassUAG(theEnv,ctmp);
     }
   PutClassInTable(theEnv,cls);

   BuildSubclassLinks(theEnv,cls);
   InstallClass(theEnv,cls,TRUE);
   AddConstructToModule((struct constructHeader *) cls);

   FormInstanceTemplate(theEnv,cls);
   FormSlotNameMap(theEnv,cls);

   AssignClassID(theEnv,cls);

#if DEBUGGING_FUNCTIONS
   if (cls->abstract)
     {
      cls->traceInstances = FALSE;
      cls->traceSlots = FALSE;
     }
   else
     {
      if (oldTraceInstances)
        cls->traceInstances = TRUE;
      if (oldTraceSlots)
        cls->traceSlots = TRUE;
     }
#endif

#if DEBUGGING_FUNCTIONS
   if (EnvGetConserveMemory(theEnv) == FALSE)
     SetDefclassPPForm((void *) cls,CopyPPBuffer(theEnv));
#endif

#if DEFMODULE_CONSTRUCT


   CreateClassScopeMap(theEnv,cls);

#endif


   CreatePublicSlotMessageHandlers(theEnv,cls);
  }
