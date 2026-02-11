sge_write_pid(const char *pid_log_file)
{
   int pid;
   FILE *fp;

   DENTER(TOP_LAYER, "sge_write_pid");

   close(creat(pid_log_file, 0644));
#if defined( INTERIX )


   chown(pid_log_file, geteuid(), -1);
#endif
   if ((fp = fopen(pid_log_file, "w")) != NULL) {
      pid = getpid();
      FPRINTF((fp, "%d\n", pid));
      FCLOSE(fp);
   }
   DEXIT;
   return;
FPRINTF_ERROR:
FCLOSE_ERROR:

   DEXIT;
   return;
}
