HandleSignal(int signum)

{
if (signum != SIGCHLD)
   {
   snprintf(OUTPUT,CF_BUFSIZE*2,"Received signal %d (%s) while doing [%s]",signum,SIGNALS[signum],CFLOCK);
   Chop(OUTPUT);
   CfLog(cferror,OUTPUT,"");
   snprintf(OUTPUT,CF_BUFSIZE*2,"Logical start time %s ",ctime(&CFSTARTTIME));
   Chop(OUTPUT);
   CfLog(cferror,OUTPUT,"");
   snprintf(OUTPUT,CF_BUFSIZE*2,"This sub-task started really at %s\n",ctime(&CFINITSTARTTIME));
   CfLog(cferror,OUTPUT,"");
   fflush(stdout);

   if (signum == SIGTERM || signum == SIGINT || signum == SIGHUP || signum == SIGSEGV || signum == SIGKILL|| signum == SIGPIPE)
      {
      unlink(PIDFILE);
      ReleaseCurrentLock();
      CloseAuditLog();
      closelog();
      exit(0);
      }
   else if (signum == SIGUSR1)
      {
      DEBUG= true;
      D2= true;
      }
   else if (signum == SIGUSR2)
      {
      DEBUG= false;
      D2= false;
      }
   else
      {
      }


   signal(signum,HandleSignal);
   }
}
