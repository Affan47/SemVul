show_disabled_jobs(UAContext *ua)
{
   JOB *job;
   bool first = true;
   foreach_res(job, R_JOB) {
      if (!acl_access_ok(ua, Job_ACL, job->name())) {
         continue;
      }
      if (!job->enabled) {
         if (first) {
            first = false;
            ua->send_msg(_("Disabled Jobs:\n"));
         }
         ua->send_msg("   %s\n", job->name());
     }
  }
  if (first) {
     ua->send_msg(_("No disabled Jobs.\n"));
  }
}
