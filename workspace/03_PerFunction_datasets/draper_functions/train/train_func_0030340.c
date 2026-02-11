create_unique_job_name(JCR *jcr, const char *base_name)
{

   static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
   static time_t last_start_time = 0;
   static int seq = 0;
   time_t now = time(NULL);
   struct tm tm;
   char dt[MAX_TIME_LENGTH];
   char name[MAX_NAME_LENGTH];
   char *p;
   int len;


   P(mutex);
   seq++;
   if (seq > 59) {
      seq = 0;
      while (now == last_start_time) {
         bmicrosleep(0, 500000);
         now = time(NULL);
      }
   }
   last_start_time = now;
   V(mutex);
   jcr->start_time = now;

   (void)localtime_r(&now, &tm);

   strftime(dt, sizeof(dt), "%Y-%m-%d_%H.%M.%S", &tm);
   len = strlen(dt) + 5;
   bstrncpy(name, base_name, sizeof(name));
   name[sizeof(name)-len] = 0;
   bsnprintf(jcr->Job, sizeof(jcr->Job), "%s.%s_%02d", name, dt, seq);

   for (p=jcr->Job; *p; p++) {
      if (*p == ' ') {
         *p = '_';
      }
   }
   Dmsg2(100, "JobId=%u created Job=%s\n", jcr->JobId, jcr->Job);
}
