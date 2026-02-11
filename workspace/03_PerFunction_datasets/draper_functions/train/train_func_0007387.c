_prof_get_info_string(prof_level level, dstring *info_string, bool with_sub, dstring *error)
{
   pthread_t thread_id = pthread_self();
   int thread_num;
   dstring level_string = DSTRING_INIT;
   const char *ret = NULL;
   double busy, utime, stime, utilization;

   thread_num = get_prof_info_thread_id(thread_id);

   busy        = prof_get_total_busy(level, with_sub, error);
   utime       = prof_get_total_utime(level, with_sub, error);
   stime       = prof_get_total_stime(level, with_sub, error);
   utilization = busy > 0 ? (utime + stime) / busy * 100 : 0;

   sge_dstring_sprintf(&level_string, PROF_GET_INFO_FORMAT,
     theInfo[thread_num][level].name, busy, utime, stime, utilization);

   ret = sge_dstring_append_dstring(info_string, &level_string);
   sge_dstring_free(&level_string);

   return ret;
}
