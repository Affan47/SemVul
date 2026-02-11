schedd_log(const char *logstr, lList **monitor_alpp, bool monitor_next_run)
{
   DENTER(TOP_LAYER, "schedd_log");

   if (monitor_alpp) {

      answer_list_add(monitor_alpp, logstr, STATUS_ESEMANTIC, ANSWER_QUALITY_ERROR);
   }

   if (monitor_next_run){

      time_t now;
      FILE *fp = NULL;
      char *time_str = NULL;
      char str[128];

      now = (time_t)sge_get_gmt();
      time_str =  ctime_r(&now, str);
      if (time_str[strlen(time_str) - 1] == '\n') {
         time_str[strlen(time_str) - 1] = '|';
      }

      fp = fopen(schedd_log_file, "a");
      if (!fp) {
         DPRINTF(("could not open schedd_log_file "SFQ"\n", schedd_log_file));
         DEXIT;
         return -1;
      }

      fprintf(fp, "%s", time_str);
      fprintf(fp, "%s\n", logstr);
      FCLOSE(fp);
   }

   DRETURN(0);
FCLOSE_ERROR:
   DPRINTF((MSG_FILE_ERRORCLOSEINGXY_SS, schedd_log_file, strerror(errno)));
   DRETURN(-1);
}
