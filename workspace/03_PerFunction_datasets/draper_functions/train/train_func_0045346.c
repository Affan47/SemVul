prof_get_measurement_wallclock(prof_level level, bool with_sub, dstring *error)
{
   pthread_t thread_id;
   int thread_num;
   clock_t clock = 0;
   double ret = 0.0;

   if (level >= SGE_PROF_ALL) {
      sge_dstring_sprintf_append(error, MSG_PROF_INVALIDLEVEL_SD, "prof_get_measurement_wallclock", level);
   } else if (profiling_enabled) {
      thread_id = pthread_self();

      thread_num = get_prof_info_thread_id(thread_id);

      if ((thread_num < 0) || (thread_num >= MAX_THREAD_NUM)) {
         sge_dstring_sprintf_append(error, MSG_PROF_MAXTHREADSEXCEEDED_S, "prof_get_measurement_wallclock");
      } else {
         clock = theInfo[thread_num][level].end - theInfo[thread_num][level].start;

         if (!with_sub) {
            clock -= theInfo[thread_num][level].sub;
         }
      }

      ret = clock * 1.0 / sysconf(_SC_CLK_TCK);
   }

   return ret;
}
