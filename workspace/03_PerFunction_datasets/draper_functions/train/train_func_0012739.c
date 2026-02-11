cl_commlib_check_callback_functions(void) {


    cl_thread_settings_t* actual_thread = NULL;
    cl_bool_t is_commlib_thread = CL_FALSE;

    switch(cl_com_create_threads) {
       case CL_NO_THREAD:
          break;
       default:
          actual_thread = cl_thread_get_thread_config();
          if (actual_thread != NULL) {
             if (actual_thread->thread_type == CL_TT_COMMLIB) {
                CL_LOG(CL_LOG_INFO, "called by commlib internal thread");
                is_commlib_thread = CL_TRUE;
             }
          }
          break;
    }


    if ( is_commlib_thread == CL_FALSE ) {
       cl_application_error_list_elem_t* elem = NULL;

       CL_LOG(CL_LOG_INFO, "called by commlib external thread");


       pthread_mutex_lock(&cl_com_error_mutex);
       cl_raw_list_lock(cl_com_application_error_list);
       while( (elem = cl_application_error_list_get_first_elem(cl_com_application_error_list)) != NULL ) {
          cl_raw_list_remove_elem(cl_com_application_error_list, elem->raw_elem);


          if (cl_com_error_status_func != NULL) {
             CL_LOG(CL_LOG_INFO,"triggering application error function");
             cl_com_error_status_func(elem);
          } else {
             CL_LOG(CL_LOG_WARNING,"can't trigger application error function: no function set");
          }

          free(elem->cl_info);
          free(elem);
          elem = NULL;
       }
       cl_raw_list_unlock(cl_com_application_error_list);
       pthread_mutex_unlock(&cl_com_error_mutex);
    }
    return CL_RETVAL_OK;
}
