EnvUndefinstances(
  void *theEnv,
  void *vptr)
  {
#if RUN_TIME || BLOAD_ONLY
#if MAC_MCW || IBM_MCW || MAC_XCD
#pragma unused(theEnv,vptr)
#endif
   return(FALSE);
#else
   DEFINSTANCES *dptr;

   dptr = (DEFINSTANCES *) vptr;

#if BLOAD || BLOAD_AND_BSAVE
   if (Bloaded(theEnv))
     return(FALSE);
#endif
   if (dptr == NULL)
     return(RemoveAllDefinstances(theEnv));
   if (EnvIsDefinstancesDeletable(theEnv,vptr) == FALSE)
     return(FALSE);
   RemoveConstructFromModule(theEnv,(struct constructHeader *) vptr);
   RemoveDefinstances(theEnv,(void *) dptr);
   return(TRUE);
#endif
  }
