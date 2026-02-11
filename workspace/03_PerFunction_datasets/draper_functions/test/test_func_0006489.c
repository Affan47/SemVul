cl_dump_ssl_private(cl_com_connection_t* connection) {

   cl_com_ssl_private_t* private = NULL;
   if (connection == NULL) {
      CL_LOG(CL_LOG_DEBUG, "connection is NULL");
   } else {
      if ( (private=cl_com_ssl_get_private(connection)) != NULL) {
         CL_LOG_INT(CL_LOG_DEBUG,"server port:   ",private->server_port);
         CL_LOG_INT(CL_LOG_DEBUG,"connect_port:  ",private->connect_port);
         CL_LOG_INT(CL_LOG_DEBUG,"socked fd:     ",private->sockfd);
         CL_LOG_INT(CL_LOG_DEBUG,"ssl_last_error:",private->ssl_last_error);
         if (private->ssl_ctx == NULL) {
            CL_LOG_STR(CL_LOG_DEBUG,"ssl_ctx:       ", "n.a.");
         } else {
            CL_LOG_STR(CL_LOG_DEBUG,"ssl_ctx:       ", "initialized");
         }
         if (private->ssl_obj == NULL) {
            CL_LOG_STR(CL_LOG_DEBUG,"ssl_obj:       ", "n.a.");
         } else {
            CL_LOG_STR(CL_LOG_DEBUG,"ssl_obj:       ", "initialized");
         }
         if (private->ssl_bio_socket == NULL) {
            CL_LOG_STR(CL_LOG_DEBUG,"ssl_bio_socket:", "n.a.");
         } else {
            CL_LOG_STR(CL_LOG_DEBUG,"ssl_bio_socket:", "initialized");
         }
         if (private->ssl_setup == NULL) {
            CL_LOG_STR(CL_LOG_DEBUG,"ssl_setup:     ", "n.a.");
         } else {
            CL_LOG_STR(CL_LOG_DEBUG,"ssl_setup:     ", "initialized");
         }
         if (private->ssl_unique_id == NULL) {
            CL_LOG_STR(CL_LOG_DEBUG,"ssl_unique_id: ", "n.a.");
         } else {
            CL_LOG_STR(CL_LOG_DEBUG,"ssl_unique_id: ", private->ssl_unique_id);
         }
      }
   }
}
