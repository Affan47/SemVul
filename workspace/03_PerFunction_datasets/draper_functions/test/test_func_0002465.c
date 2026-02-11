term_last_jobs_list()
{
   if (last_jobs) {
      lock_last_jobs_list();
      while (!last_jobs->empty()) {
         void *je = last_jobs->first();
         last_jobs->remove(je);
         free(je);
      }
      delete last_jobs;
      last_jobs = NULL;
      unlock_last_jobs_list();
   }
   if (jcrs) {
      delete jcrs;
      jcrs = NULL;
   }
}
