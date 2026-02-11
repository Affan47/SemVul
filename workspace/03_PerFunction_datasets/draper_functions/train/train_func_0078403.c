EnvUndeffunction(
  void *theEnv,
  void *vptr)
  {
#if (MAC_MCW || IBM_MCW) && (RUN_TIME || BLOAD_ONLY)
#pragma unused(theEnv,vptr)
#endif

#if BLOAD_ONLY || RUN_TIME
   return(FALSE);
#else

#if BLOAD || BLOAD_AND_BSAVE

   if (Bloaded(theEnv) == TRUE)
     return(FALSE);
#endif
   if (vptr == NULL)
      return(RemoveAllDeffunctions(theEnv));
   if (EnvIsDeffunctionDeletable(theEnv,vptr) == FALSE)
     return(FALSE);
   RemoveConstructFromModule(theEnv,(struct constructHeader *) vptr);
   RemoveDeffunction(theEnv,vptr);
   return(TRUE);
#endif
  }
