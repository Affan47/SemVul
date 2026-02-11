EnvIsDefmethodDeletable(
  void *theEnv,
  void *ptr,
  unsigned theIndex)
  {
   if (! ConstructsDeletable(theEnv))
     { return FALSE; }

   if (((DEFGENERIC *) ptr)->methods[FindMethodByIndex((DEFGENERIC *) ptr,theIndex)].system)
     return(FALSE);

#if (! BLOAD_ONLY) && (! RUN_TIME)
   return((MethodsExecuting((DEFGENERIC *) ptr) == FALSE) ? TRUE : FALSE);
#else
   return FALSE;
#endif
  }
