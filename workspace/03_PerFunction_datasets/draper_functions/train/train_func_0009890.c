submit_thread(void *arg)
{
   drmaa_job_template_t *jt = NULL;
   char jobid[DRMAA_JOBNAME_BUFFER];
   const char *job_argv[2] = {"5", NULL};
   int check_count = 1;

   drmaa_allocate_job_template (&jt, NULL, 0);
   drmaa_set_attribute (jt, DRMAA_REMOTE_COMMAND, (char *)arg, NULL, 0);
   drmaa_set_vector_attribute(jt, DRMAA_V_ARGV, job_argv, NULL, 0);
   drmaa_set_attribute (jt, DRMAA_OUTPUT_PATH, ":"DRMAA_PLACEHOLDER_HD"/DRMAA_JOB", NULL, 0);
   drmaa_set_attribute (jt, DRMAA_JOIN_FILES, "y", NULL, 0);

   while (drmaa_run_job (jobid, DRMAA_JOBNAME_BUFFER, jt, NULL, 0) == DRMAA_ERRNO_SUCCESS) {
      if (check_count) {
         LOCK_COUNT();

         if (count < 0) {
            count = 0;
         }

         UNLOCK_COUNT();

         check_count = 0;
      }
   }

   drmaa_delete_job_template (jt, NULL, 0);

   return (void *)NULL;
}
