EnvGetInstancePPForm(
  void *theEnv,
  char *buf,
  unsigned buflen,
  void *iptr)
  {
   char *pbuf = "***InstancePPForm***";

   if (((INSTANCE_TYPE *) iptr)->garbage == 1)
     return;
   if (OpenStringDestination(theEnv,pbuf,buf,buflen+1) == 0)
     return;
   PrintInstance(theEnv,pbuf,(INSTANCE_TYPE *) iptr," ");
   CloseStringDestination(theEnv,pbuf);
  }
