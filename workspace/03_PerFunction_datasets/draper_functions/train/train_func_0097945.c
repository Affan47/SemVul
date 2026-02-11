GetcString(
  void *theEnv,
  char *logicalName)
  {
   struct stringRouter *head;
   int rc;

   head = FindStringRouter(theEnv,logicalName);
   if (head == NULL)
     {
      SystemError(theEnv,"ROUTER",1);
      EnvExitRouter(theEnv,EXIT_FAILURE);
     }

   if (head->readWriteType != READ_STRING) return(EOF);
   if (head->currentPosition >= (int) head->maximumPosition)
     {
      head->currentPosition++;
      return(EOF);
     }

   rc = (unsigned char) head->str[head->currentPosition];
   head->currentPosition++;

   return(rc);
  }
