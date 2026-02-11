cl_com_set_handle_fds(cl_com_handle_t* handle, int** fdArrayBack, unsigned long* fdCountBack) {
   int fd = -1;
   int handle_fd = -1;
   unsigned long fd_count = 0;
   int* fd_array = NULL;
   unsigned long fdArrayIndex = 0;
   int ret_val = CL_RETVAL_UNKNOWN;
   cl_connection_list_elem_t* elem = NULL;
   cl_com_connection_t* connection = NULL;

   if (handle == NULL || fdArrayBack == NULL || fdCountBack == NULL || *fdArrayBack != NULL) {
      return CL_RETVAL_PARAMS;
   }

   *fdCountBack = 0;


   pthread_mutex_lock(&cl_com_handle_list_mutex);

   if (cl_com_handle_list  == NULL) {
      pthread_mutex_unlock(&cl_com_handle_list_mutex);
      CL_LOG(CL_LOG_ERROR,"cl_com_setup_commlib() not called");
      return CL_RETVAL_PARAMS;
   }


   cl_raw_list_lock(cl_com_handle_list);

   if (handle->service_handler != NULL) {
      if (cl_com_connection_get_fd(handle->service_handler, &handle_fd) == CL_RETVAL_OK) {
         CL_LOG_INT(CL_LOG_INFO, "service handle port: ", handle_fd);
         fd_count++;
         ret_val = CL_RETVAL_OK;
      }
   }

   cl_raw_list_lock(handle->connection_list);

   fd_count += cl_raw_list_get_elem_count(handle->connection_list);
   if (fd_count > 0) {
      fd_array = (int*) malloc(sizeof(int) * fd_count);
      if (fd_array == NULL) {
         cl_raw_list_unlock(handle->connection_list);
         cl_raw_list_unlock(cl_com_handle_list);
         pthread_mutex_unlock(&cl_com_handle_list_mutex);
         return CL_RETVAL_MALLOC;
      }
   }

   if (handle_fd != -1) {
      if (fdArrayIndex < fd_count) {
         CL_LOG_INT(CL_LOG_INFO, "adding service handle port fd: ", handle_fd);
         fd_array[fdArrayIndex] = handle_fd;
         fdArrayIndex++;
      }
   }

   elem = cl_connection_list_get_first_elem(handle->connection_list);
   while(elem) {
      connection = elem->connection;
      if (cl_com_connection_get_fd(connection, &fd) == CL_RETVAL_OK) {
         if (fdArrayIndex < fd_count) {
            CL_LOG_INT(CL_LOG_INFO, "adding fd for connection: ", fd);
            fd_array[fdArrayIndex] = fd;
            fdArrayIndex++;
         }
         ret_val = CL_RETVAL_OK;
      }
      elem = cl_connection_list_get_next_elem(elem);
   }
   cl_raw_list_unlock(handle->connection_list);
   cl_raw_list_unlock(cl_com_handle_list);
   pthread_mutex_unlock(&cl_com_handle_list_mutex);

   if (fdArrayIndex == 0) {
      if (fd_array != NULL) {
         free(fd_array);
         fd_array = NULL;
      }
      ret_val = CL_RETVAL_UNKNOWN;
   }

   *fdCountBack = fdArrayIndex;
   *fdArrayBack = fd_array;

   return ret_val;
}
