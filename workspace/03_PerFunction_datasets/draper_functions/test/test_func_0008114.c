cl_raw_list_setup(cl_raw_list_t** list_p, char* list_name ,int enable_list_locking) {

   if (list_p == NULL || list_name == NULL) {

      return CL_RETVAL_PARAMS;
   }

   if (*list_p != NULL) {

      return CL_RETVAL_PARAMS;
   }


   *list_p = (cl_raw_list_t*) malloc(sizeof (cl_raw_list_t));
   if (*list_p == NULL) {
      return CL_RETVAL_MALLOC;
   }
   memset(*list_p, 0, sizeof(cl_raw_list_t));

   (*list_p)->list_name = strdup(list_name);
   if ((*list_p)->list_name == NULL) {
      free(*list_p);
      *list_p = NULL;
   }

   if (enable_list_locking) {

      (*list_p)->list_mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
      if ( (*list_p)->list_mutex == NULL) {
         cl_raw_list_cleanup(list_p);
         return CL_RETVAL_MALLOC;
      }
      if (pthread_mutex_init((*list_p)->list_mutex, NULL) != 0) {
         CL_LOG_STR(CL_LOG_ERROR,"raw list mutex init setup error for list:", (*list_p)->list_name);
         cl_raw_list_cleanup(list_p);
         return CL_RETVAL_MUTEX_ERROR;
      }
   }
#ifdef CL_DO_COMMLIB_DEBUG
   CL_LOG_STR(CL_LOG_DEBUG,"raw list setup complete for list:",(*list_p)->list_name);
#endif
   return CL_RETVAL_OK;
}
