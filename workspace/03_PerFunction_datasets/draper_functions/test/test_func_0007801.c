EnvListDefmessageHandlers(
  void *theEnv,
  char *logName,
  void *vptr,
  int inhp)
  {
   DEFCLASS *cls;
   long cnt;
   PACKED_CLASS_LINKS plinks;

   if (vptr != NULL)
     {
      cls = (DEFCLASS *) vptr;
      if (inhp)
        cnt = DisplayHandlersInLinks(theEnv,logName,&cls->allSuperclasses,0);
      else
        {
         plinks.classCount = 1;
         plinks.classArray = &cls;
         cnt = DisplayHandlersInLinks(theEnv,logName,&plinks,0);
        }
     }
   else
     {
      plinks.classCount = 1;
      cnt = 0L;
      for (cls = (DEFCLASS *) EnvGetNextDefclass(theEnv,NULL) ;
           cls != NULL ;
           cls = (DEFCLASS *) EnvGetNextDefclass(theEnv,(void *) cls))
        {
         plinks.classArray = &cls;
         cnt += DisplayHandlersInLinks(theEnv,logName,&plinks,0);
        }
     }
   PrintTally(theEnv,logName,cnt,"message-handler","message-handlers");
  }
