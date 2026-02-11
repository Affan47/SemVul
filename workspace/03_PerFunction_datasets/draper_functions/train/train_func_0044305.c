cl_com_ssl_get_unique_id(cl_com_handle_t* handle,
                             char* un_resolved_hostname, char* component_name, unsigned long component_id,
                             char** uniqueIdentifier ) {
   char* unique_hostname = NULL;
   cl_com_endpoint_t client;
   cl_com_connection_t* connection = NULL;
   cl_connection_list_elem_t* elem = NULL;
   cl_com_ssl_private_t* private = NULL;
   int function_return_value = CL_RETVAL_UNKNOWN_ENDPOINT;
   int return_value = CL_RETVAL_OK;

   if (handle               == NULL ||
       un_resolved_hostname == NULL ||
       component_name       == NULL ||
       uniqueIdentifier     == NULL   ) {
      return CL_RETVAL_PARAMS;
   }

   if (*uniqueIdentifier != NULL) {
      CL_LOG(CL_LOG_ERROR,"uniqueIdentifer is already set");
      return CL_RETVAL_PARAMS;
   }


   return_value = cl_com_cached_gethostbyname(un_resolved_hostname, &unique_hostname,NULL, NULL, NULL);
   if (return_value != CL_RETVAL_OK) {
      CL_LOG(CL_LOG_ERROR,cl_get_error_text(return_value));
      return return_value;
   }


   client.comp_host = unique_hostname;
   client.comp_name = component_name;
   client.comp_id   = component_id;


   cl_raw_list_lock(handle->connection_list);

   elem = cl_connection_list_get_first_elem(handle->connection_list);
   while(elem) {
      connection = elem->connection;
      if (connection != NULL) {

         if ( cl_com_compare_endpoints(connection->remote, &client) ) {
            private = cl_com_ssl_get_private(connection);
            if (private != NULL) {
               if (private->ssl_unique_id != NULL) {
                  *uniqueIdentifier = strdup(private->ssl_unique_id);
                  if ( *uniqueIdentifier == NULL) {
                     function_return_value = CL_RETVAL_MALLOC;
                  } else {
                     function_return_value = CL_RETVAL_OK;
                  }
                  break;
               }
            }
         }
      }
      elem = cl_connection_list_get_next_elem(elem);
   }


   cl_raw_list_unlock(handle->connection_list);
   free(unique_hostname);
   unique_hostname = NULL;
   return function_return_value;
}
