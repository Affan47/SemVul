EnvUndefclass(
  void *theEnv,
  void *theDefclass)
  {
#if (MAC_MCW || IBM_MCW) && (RUN_TIME || BLOAD_ONLY)
#pragma unused(theEnv,theDefclass)
#endif

#if RUN_TIME || BLOAD_ONLY
   return(FALSE);
#else
   DEFCLASS *cls;

   cls = (DEFCLASS *) theDefclass;
#if BLOAD || BLOAD_AND_BSAVE
   if (Bloaded(theEnv))
     return(FALSE);
#endif
   if (cls == NULL)
     return(RemoveAllUserClasses(theEnv));
   return(DeleteClassUAG(theEnv,cls));
#endif
  }
