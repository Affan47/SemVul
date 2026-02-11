FactJNCompVars1(
  void *theEnv,
  void *theValue,
  DATA_OBJECT *theResult)
  {
#if MAC_MCW || IBM_MCW || MAC_XCD
#pragma unused(theResult)
#endif
   int p1, e1, p2, e2;
   struct fact *fact1, *fact2;
   struct factCompVarsJN1Call *hack;


   hack = (struct factCompVarsJN1Call *) ValueToBitMap(theValue);


   p1 = EngineData(theEnv)->GlobalJoin->depth - 1;
   p2 = ((int) hack->pattern2) - 1;

   fact1 = (struct fact *) EngineData(theEnv)->GlobalRHSBinds->binds[0].gm.theMatch->matchingItem;
   if (p1 != p2)
     { fact2 = (struct fact *) EngineData(theEnv)->GlobalLHSBinds->binds[p2].gm.theMatch->matchingItem; }
   else
     { fact2 = fact1; }


   e1 = (int) hack->slot1;
   e2 = (int) hack->slot2;

   if (fact1->theProposition.theFields[e1].type !=
       fact2->theProposition.theFields[e2].type)
     { return((int) hack->fail); }

   if (fact1->theProposition.theFields[e1].value !=
       fact2->theProposition.theFields[e2].value)
     { return((int) hack->fail); }

   return((int) hack->pass);
  }
