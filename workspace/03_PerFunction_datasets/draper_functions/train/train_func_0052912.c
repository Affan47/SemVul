ooCreateCmdConnection()
{
   int ret = 0;
   int thePipe[2];

   if ((ret = pipe(thePipe)) == -1) {
      return OO_FAILED;
   }
   ast_mutex_init(&gCmdChanLock);

   gH323ep.cmdSock = dup(thePipe[0]);
   close(thePipe[0]);
   gCmdChan = dup(thePipe[1]);
   close(thePipe[1]);
   return OO_OK;
}
