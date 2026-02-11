DisplaySeparator(
  void *theEnv,
  char *logicalName,
  char *buf,
  int maxlen,
  int sepchar)
  {
   register int i;

   for (i = 0 ; i < maxlen-2 ; i++)
     buf[i] = (char) sepchar;
   buf[i++] = '\n';
   buf[i] = '\0';
   EnvPrintRouter(theEnv,logicalName,buf);
  }
