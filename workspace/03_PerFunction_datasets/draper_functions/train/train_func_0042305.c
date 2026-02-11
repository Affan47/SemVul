MarkObjectPtnIncrementalReset(
  void *theEnv,
  struct patternNodeHeader *thePattern,
  int value)
  {
#if MAC_MCW || IBM_MCW || MAC_XCD
#pragma unused(theEnv)
#endif

   if (thePattern->initialize == FALSE)
     return;
   thePattern->initialize = value;
  }
