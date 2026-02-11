select_restore_job_resource(UAContext *ua)
{
   char name[MAX_NAME_LENGTH];
   JOB *job;

   start_prompt(ua, _("The defined Restore Job resources are:\n"));
   LockRes();
   foreach_res(job, R_JOB) {
      if (job->JobType == JT_RESTORE && acl_access_ok(ua, Job_ACL, job->name())) {
         add_prompt(ua, job->name());
      }
   }
   UnlockRes();
   if (do_prompt(ua, _("Job"), _("Select Restore Job"), name, sizeof(name)) < 0) {
      return NULL;
   }
   job = (JOB *)GetResWithName(R_JOB, name);
   return job;
}
