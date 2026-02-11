sge_prof_cleanup(void) {

   if (!profiling_enabled) {
      return;
   }

   pthread_mutex_lock(&thrdInfo_mutex);

   pthread_key_delete (thread_id_key);

   if (theInfo != NULL) {
      int c, i;

      for (c = 0; c < MAX_THREAD_NUM; c++) {
         for (i = 0; i <= SGE_PROF_ALL; i++) {
            if ( theInfo[c] != NULL) {
               sge_dstring_free(&theInfo[c][i].info_string);
            }
         }

         FREE(theInfo[c]);
      }

      FREE(theInfo);
   }

   FREE(thrdInfo);

   sge_prof_array_initialized = 0;

   pthread_mutex_unlock(&thrdInfo_mutex);

}
