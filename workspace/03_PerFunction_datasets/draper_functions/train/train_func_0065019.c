PackClassLinks(
  void *theEnv,
  PACKED_CLASS_LINKS *plinks,
  CLASS_LINK *lptop)
  {
   register unsigned count;
   register CLASS_LINK *lp;

   for (count = 0 , lp = lptop ; lp != NULL ; lp = lp->nxt)
     count++;
   if (count > 0)
     plinks->classArray = (DEFCLASS **) gm2(theEnv,(sizeof(DEFCLASS *) * count));
   else
     plinks->classArray = NULL;
   for (count = 0 , lp = lptop ; lp != NULL ; lp = lp->nxt , count++)
     plinks->classArray[count] = lp->cls;
   DeleteClassLinks(theEnv,lptop);
   plinks->classCount = (unsigned short) count;
  }
