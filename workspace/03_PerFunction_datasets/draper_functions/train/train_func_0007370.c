init_array_first(void) {

   if (sge_prof_array_initialized == 0) {
      pthread_mutex_lock(&thrdInfo_mutex);

      if (pthread_key_create (&thread_id_key, NULL) == 0) {
         theInfo = (sge_prof_info_t**)sge_malloc(MAX_THREAD_NUM * sizeof(sge_prof_info_t*));
         memset (theInfo, 0, MAX_THREAD_NUM * sizeof(sge_prof_info_t*));
         sge_prof_array_initialized = 1;
      }

      pthread_mutex_unlock(&thrdInfo_mutex);
   }

}
