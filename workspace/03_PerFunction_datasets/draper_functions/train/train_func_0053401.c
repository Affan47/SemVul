EnvSetDefruleWatchFirings(
  void *theEnv,
  unsigned newState,
  void *rulePtr)
  {
   struct defrule *thePtr;
#if MAC_MCW || IBM_MCW || MAC_XCD
#pragma unused(theEnv)
#endif

   for (thePtr = (struct defrule *) rulePtr;
        thePtr != NULL;
        thePtr = thePtr->disjunct)
     { thePtr->watchFiring = newState; }
  }
