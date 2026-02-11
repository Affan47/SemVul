FindApplicableHandlers(
  void *theEnv,
  DEFCLASS *cls,
  SYMBOL_HN *mname)
  {
   register int i;
   HANDLER_LINK *tops[4],*bots[4];

   for (i = MAROUND ; i <= MAFTER ; i++)
     tops[i] = bots[i] = NULL;

   for (i = 0 ; i < cls->allSuperclasses.classCount ; i++)
     FindApplicableOfName(theEnv,cls->allSuperclasses.classArray[i],tops,bots,mname);
   return(JoinHandlerLinks(theEnv,tops,bots,mname));
  }
