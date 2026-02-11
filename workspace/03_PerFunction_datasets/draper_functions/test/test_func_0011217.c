direct_log(IPC_Channel* ch, gpointer user_data)
{
	IPC_Message*		ipcmsg;
	GMainLoop*		loop;
	int			pri = LOG_DEBUG + 1;

	loop =(GMainLoop*)user_data;

	while(ch->ops->is_message_pending(ch)){
		if (ch->ch_status == IPC_DISCONNECT){
			cl_log(LOG_ERR, "read channel is disconnected:"
			       "something very wrong happened");
			return FALSE;
		}

		ipcmsg = getIPCmsg(ch);
		if (ipcmsg == NULL){
			return TRUE;
		}

		if( ipcmsg->msg_body
		    && ipcmsg->msg_len > 0 ){
			LogDaemonMsgHdr *logmsghdr;
			LogDaemonMsgHdr	copy;
			char *msgtext;

			logmsghdr = (LogDaemonMsgHdr*) ipcmsg->msg_body;


#define	COPYFIELD(copy, msg, field) memcpy(((u_char*)&copy.field), ((u_char*)&msg->field), sizeof(copy.field))
			COPYFIELD(copy, logmsghdr, use_pri_str);
			COPYFIELD(copy, logmsghdr, entity);
			COPYFIELD(copy, logmsghdr, entity_pid);
			COPYFIELD(copy, logmsghdr, timestamp);
			COPYFIELD(copy, logmsghdr, priority);


			msgtext = (char *)logmsghdr + sizeof(LogDaemonMsgHdr);
			cl_direct_log(copy.priority, msgtext
			,	copy.use_pri_str
			,	copy.entity, copy.entity_pid
			,	copy.timestamp);

			if (copy.priority < pri)
				pri = copy.priority;

			(void)logd_log;


			if (ipcmsg->msg_done){
				ipcmsg->msg_done(ipcmsg);
			}
		}
	}


	cl_log_do_fflush(pri <= LOG_ERR);

	if(needs_shutdown) {
		cl_log(LOG_INFO, "Exiting write process");
		g_main_quit(loop);
		return FALSE;
	}
	return TRUE;
}
