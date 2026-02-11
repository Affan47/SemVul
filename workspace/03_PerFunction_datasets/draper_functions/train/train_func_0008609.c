ssh_message_queue(ssh_session session, ssh_message message){
    if (message != NULL) {
#ifdef WITH_SERVER
	int ret;


        ret = ssh_execute_server_callbacks(session, message);
        if (ret == SSH_OK){
            ssh_message_free(message);
            return;
        }
#endif
        if(session->ssh_message_callback != NULL) {
            ssh_execute_message_callback(session, message);
            return;
        }
        if (session->server_callbacks != NULL){


            ssh_message_reply_default(message);
            ssh_message_free(message);
            return;
        }
        if(session->ssh_message_list == NULL) {
            session->ssh_message_list = ssh_list_new();
        }
        if (session->ssh_message_list != NULL) {
            ssh_list_append(session->ssh_message_list, message);
        }
    }
}
