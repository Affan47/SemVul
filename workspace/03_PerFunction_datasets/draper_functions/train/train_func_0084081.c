my_log_flush_list(cl_raw_list_t* list_p) {
   int ret_val;
   cl_log_list_elem_t* elem = NULL;


   if (list_p == NULL) {
      return CL_RETVAL_LOG_NO_LOGLIST;
   }

   if (  ( ret_val = cl_raw_list_lock(list_p)) != CL_RETVAL_OK) {
      return ret_val;
   }

   while ( (elem = cl_log_list_get_first_elem(list_p) ) != NULL) {
      char* param;
      if (elem->log_parameter == NULL) {
         param = "";
      } else {
         param = elem->log_parameter;
      }
      printf("%-15s|%-10s|%s%s\n",elem->log_thread_name,cl_log_list_convert_type_id(elem->log_type),elem->log_message,param);
      cl_log_list_del_log(list_p);
   }

   if (  ( ret_val = cl_raw_list_unlock(list_p)) != CL_RETVAL_OK) {
      return ret_val;
   }
   return CL_RETVAL_OK;
}
