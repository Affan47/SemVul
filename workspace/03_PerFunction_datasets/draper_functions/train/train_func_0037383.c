EnvIsDefmessageHandlerDeletable(
  void *theEnv,
  void *ptr,
  unsigned theIndex)
  {
   DEFCLASS *cls;

   if (! ConstructsDeletable(theEnv))
     { return FALSE; }

   cls = (DEFCLASS *) ptr;
   if (cls->handlers[theIndex-1].system == 1)
     return(FALSE);

#if (! BLOAD_ONLY) && (! RUN_TIME)
   return((HandlersExecuting(cls) == FALSE) ? TRUE : FALSE);
#else
   return FALSE;
#endif
  }
