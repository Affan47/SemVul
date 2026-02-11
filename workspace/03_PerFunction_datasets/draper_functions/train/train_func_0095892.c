_prof_get_total_utime(prof_level level, bool with_sub, dstring *error)
{
   pthread_t thread_id = pthread_self();
   int thread_num;
   clock_t clock = 0;

   thread_num = get_prof_info_thread_id(thread_id);

   clock = theInfo[thread_num][level].total_utime;

   if (!with_sub) {
      clock -= theInfo[thread_num][level].sub_total_utime;
   }

   return clock * 1.0 / sysconf(_SC_CLK_TCK);
}
