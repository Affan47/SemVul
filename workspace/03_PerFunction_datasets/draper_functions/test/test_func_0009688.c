map_signal(int sig)
{
   int ret = sig;

   if (sig == SIGTTIN) {


      FILE *signal_file = fopen("signal", "r");

      if (signal_file != NULL) {
         fscanf(signal_file, "%d", &ret);
         FCLOSE(signal_file);
      }
   } else if (sig == SIGTTOU) {

      ;
   } else if (sig == SIGUSR2) {
#ifdef SIGXCPU
      ret = SIGXCPU;
#else
      ret = SIGKILL;
#endif
   } else if (sig == SIGTSTP) {
      ret = SIGKILL;
   } else if (sig == SIGUSR1 || sig == SIGCONT) {

      ;
   } else {

      shepherd_trace("should map unmapable signal");
   }

   if (sig != ret) {
      shepherd_trace("mapped signal %s to signal %s",
                     sge_sys_sig2str(sig), sge_sys_sig2str(ret));
   } else {
      shepherd_trace("no need to map signal %s", sge_sys_sig2str(sig));
   }
   return ret;
FCLOSE_ERROR:
   shepherd_trace(MSG_FILE_ERRORCLOSEINGXY_SS, "signal", strerror(errno));
   return ret;
}
