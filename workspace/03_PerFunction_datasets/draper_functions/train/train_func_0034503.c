ooMonitorCmdChannels()
{
   int ret=0, nfds=0;
   struct timeval toMin;
   struct pollfd pfds[1];

   gMonitor = TRUE;

   toMin.tv_sec = 3;
   toMin.tv_usec = 0;

   while(1)
   {
      nfds = 0;
      ooSetCmdFDSETs(pfds, &nfds);

      if(!gMonitor) {
         OOTRACEINFO1("Ending Monitor thread\n");
         break;
      }


      if(nfds == 0)
#ifdef _WIN32
         Sleep(10);
#else
      {
         toMin.tv_sec = 0;
         toMin.tv_usec = 10000;
         ooSocketPoll(pfds, nfds, toMin.tv_usec / 1000);
      }
#endif
      else
         ret = ooSocketPoll(pfds, nfds, toMin.tv_sec * 1000 + toMin.tv_usec / 1000);

      if(ret == -1)
      {

         OOTRACEERR1("Error in poll ...exiting\n");
         exit(-1);
	 continue;
      }

      toMin.tv_sec = 2;
      toMin.tv_usec = 100000;

      ast_mutex_lock(&monitorLock);
      if(ooProcessCmdFDSETsAndTimers(pfds, nfds, &toMin) != OO_OK)
      {

         ast_mutex_unlock(&monitorLock);
         continue;
      }
      ast_mutex_unlock(&monitorLock);

   }
   return OO_OK;
}
