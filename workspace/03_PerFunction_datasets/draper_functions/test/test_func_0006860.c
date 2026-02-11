my_message_thread(void *t_conf) {
   int do_exit = 0;

   cl_thread_settings_t *thread_config = (cl_thread_settings_t*)t_conf;


   if (cl_thread_set_thread_config(thread_config) != CL_RETVAL_OK) {
      CL_LOG(CL_LOG_ERROR,"thread setup error");
      do_exit = 1;
   }


   CL_LOG(CL_LOG_INFO, "starting initialization ...");


   cl_thread_func_startup(thread_config);
   CL_LOG(CL_LOG_INFO, "starting main loop ...");

   printf(" \"%s\" -> running ...\n", thread_config->thread_name );
   rcv_messages = 0;
   snd_messages = 0;
   evc_count    = 0;


   while (do_exit == 0) {
      int ret_val = 0;
      cl_com_message_t*  message = NULL;
      cl_com_endpoint_t* sender  = NULL;

      cl_thread_func_testcancel(thread_config);

      cl_commlib_trigger(handle, 1);
      ret_val = cl_commlib_receive_message(handle, NULL, NULL, 0,
                                           CL_FALSE, 0,
                                           &message, &sender);
      if (ret_val == CL_RETVAL_OK) {
         rcv_messages++;

         if (strcmp((char*)message->message,"event") == 0) {

            int i,help;
            cl_com_free_message(&message);
            help = 0;
            for (i=0;i<MAX_EVENT_CLIENTS;i++) {
               if ( event_client_array[i] == NULL ) {
                  event_client_array[i] = sender;
                  evc_count++;
                  help=1;
                  break;
               }
            }
            if (help != 1) {
               printf(" \"%s\" -> to much connected event clients\n", thread_config->thread_name);
               cl_com_free_endpoint(&sender);
            }
         } else {

            ret_val = cl_commlib_send_message(handle, sender->comp_host, sender->comp_name, sender->comp_id,
                                      CL_MIH_MAT_NAK,
                                      &(message->message), message->message_length,
                                      NULL, 0, 0 , CL_FALSE, CL_FALSE);
            if (ret_val == CL_RETVAL_OK) {
               snd_messages++;
            }
            cl_com_free_message(&message);
            cl_com_free_endpoint(&sender);
         }
      }
   }


   cl_thread_func_cleanup(thread_config);
   return(NULL);
}
