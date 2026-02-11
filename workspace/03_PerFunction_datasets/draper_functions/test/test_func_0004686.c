ClearBload(
  void *theEnv)
  {
   unsigned long int space;
   long i;
   struct patternParser *theParser = NULL;
   struct patternEntity *theEntity = NULL;
   void *theModule;


   GetNextPatternEntity(theEnv,&theParser,&theEntity);
   while (theEntity != NULL)
     {
      (*theEntity->theInfo->base.deleteFunction)(theEnv,theEntity);
      theEntity = NULL;
      GetNextPatternEntity(theEnv,&theParser,&theEntity);
     }


   SaveCurrentModule(theEnv);
   for (theModule = EnvGetNextDefmodule(theEnv,NULL);
        theModule != NULL;
        theModule = EnvGetNextDefmodule(theEnv,theModule))
     {
      EnvSetCurrentModule(theEnv,theModule);
      RemoveAllActivations(theEnv);
     }
   RestoreCurrentModule(theEnv);
   EnvClearFocusStack(theEnv);


   for (i = 0; i < DefruleBinaryData(theEnv)->NumberOfJoins; i++)
     { FlushAlphaBetaMemory(theEnv,DefruleBinaryData(theEnv)->JoinArray[i].beta); }


   for (i = 0; i < DefruleBinaryData(theEnv)->NumberOfDefrules; i++)
     { UnmarkConstructHeader(theEnv,&DefruleBinaryData(theEnv)->DefruleArray[i].header); }


   space = DefruleBinaryData(theEnv)->NumberOfDefruleModules * sizeof(struct defruleModule);
   if (space != 0) genlongfree(theEnv,(void *) DefruleBinaryData(theEnv)->ModuleArray,space);
   DefruleBinaryData(theEnv)->NumberOfDefruleModules = 0;

   space = DefruleBinaryData(theEnv)->NumberOfDefrules * sizeof(struct defrule);
   if (space != 0) genlongfree(theEnv,(void *) DefruleBinaryData(theEnv)->DefruleArray,space);
   DefruleBinaryData(theEnv)->NumberOfDefrules = 0;

   space = DefruleBinaryData(theEnv)->NumberOfJoins * sizeof(struct joinNode);
   if (space != 0) genlongfree(theEnv,(void *) DefruleBinaryData(theEnv)->JoinArray,space);
   DefruleBinaryData(theEnv)->NumberOfJoins = 0;
  }
