run(JCR *jcr, const char *name)
{
   Dmsg1(100, "runscript: running a RUNSCRIPT object type=%d\n", cmd_type);
   POOLMEM *ecmd = get_pool_memory(PM_FNAME);
   int status;
   BPIPE *bpipe;
   char line[MAXSTRING];

   ecmd = edit_job_codes(jcr, ecmd, this->command, "", this->job_code_callback);
   Dmsg1(100, "runscript: running '%s'...\n", ecmd);
   Jmsg(jcr, M_INFO, 0, _("%s: run %s \"%s\"\n"),
        cmd_type==SHELL_CMD?"shell command":"console command", name, ecmd);

   switch (cmd_type) {
   case SHELL_CMD:
      bpipe = open_bpipe(ecmd, 0, "r");
      free_pool_memory(ecmd);
      if (bpipe == NULL) {
         berrno be;
         Jmsg(jcr, M_ERROR, 0, _("Runscript: %s could not execute. ERR=%s\n"), name,
            be.bstrerror());
         goto bail_out;
      }
      while (fgets(line, sizeof(line), bpipe->rfd)) {
         int len = strlen(line);
         if (len > 0 && line[len-1] == '\n') {
            line[len-1] = 0;
         }
         Jmsg(jcr, M_INFO, 0, _("%s: %s\n"), name, line);
      }
      status = close_bpipe(bpipe);
      if (status != 0) {
         berrno be;
         Jmsg(jcr, M_ERROR, 0, _("Runscript: %s returned non-zero status=%d. ERR=%s\n"), name,
            be.code(status), be.bstrerror(status));
         goto bail_out;
      }
      Dmsg0(100, "runscript OK\n");
      break;
   case CONSOLE_CMD:
      if (console_command) {
         if (!console_command(jcr, ecmd)) {
            goto bail_out;
         }
      }
      break;
   }
   return true;

bail_out:

   if (fail_on_error) {
      jcr->setJobStatus(JS_ErrorTerminated);
   }
   Dmsg1(100, "runscript failed. fail_on_error=%d\n", fail_on_error);
   return false;
}
