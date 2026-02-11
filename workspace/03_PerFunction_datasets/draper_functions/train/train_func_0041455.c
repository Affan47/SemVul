cl_thread_list_delete_thread_without_join(cl_raw_list_t* list_p, cl_thread_settings_t* thread) {
   int ret_val = CL_RETVAL_OK;

   if (thread == NULL) {
      return CL_RETVAL_PARAMS;
   }


   if ( (ret_val = cl_raw_list_lock(list_p)) != CL_RETVAL_OK) {
      return ret_val;
   }


   if ( (ret_val = cl_thread_list_del_thread(list_p,thread)) != CL_RETVAL_OK) {
      cl_raw_list_unlock(list_p);
      return ret_val;
   }


   if ( (ret_val = cl_raw_list_unlock(list_p)) != CL_RETVAL_OK) {
      cl_thread_shutdown(thread);
      cl_thread_join(thread);
      cl_thread_cleanup(thread);
      free(thread);
      return ret_val;
   }


   ret_val = cl_thread_cleanup(thread);
   free(thread);

   return ret_val;
}
