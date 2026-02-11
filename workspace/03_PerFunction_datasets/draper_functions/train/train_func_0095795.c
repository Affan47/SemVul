cl_commlib_send_ack_message(cl_com_connection_t* connection, cl_com_message_t* message) {
   cl_byte_t* ack_message_data = NULL;
   unsigned long ack_message_size = 0;
   unsigned long ack_message_malloc_size = 0;

   int ret_val = CL_RETVAL_OK;
   cl_com_message_t* ack_message = NULL;

   if (connection == NULL || message == NULL) {
      return CL_RETVAL_PARAMS;
   }

   ack_message_size = CL_AM_MESSAGE_SIZE;
   ack_message_size = ack_message_size + cl_util_get_ulong_number_length(message->message_id);
   ack_message_malloc_size = sizeof(cl_byte_t)* ( ack_message_size + 1);

   ack_message_data = (cl_byte_t*)malloc(ack_message_malloc_size) ;
   if (ack_message_data == NULL) {
      return CL_RETVAL_MALLOC;
   }
   snprintf((char*)ack_message_data, ack_message_malloc_size, CL_AM_MESSAGE, CL_AM_MESSAGE_VERSION, message->message_id);

   ret_val = cl_com_setup_message(&ack_message, connection, ack_message_data, ack_message_size, CL_MIH_MAT_NAK, 0, 0);
   if (ret_val != CL_RETVAL_OK) {
      return ret_val;
   }
   ack_message->message_df = CL_MIH_DF_AM;

   CL_LOG_INT(CL_LOG_INFO,"sending ack for message=", (int)message->message_id);

   ret_val = cl_message_list_append_send(connection, ack_message, 1);

   return ret_val;
}
