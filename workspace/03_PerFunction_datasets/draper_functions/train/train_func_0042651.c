send_dropped_message(gboolean use_pri_str, IPC_Channel *chan)
{
	int sendrc;
	char buf[64];
	int buf_len = 0;
	IPC_Message *drop_msg = NULL;

	memset(buf, 0, 64);
	snprintf(buf, 64, "cl_log: %d messages were dropped", drop_msg_num);
	buf_len = strlen(buf)+1;
	drop_msg = ChildLogIPCMessage(LOG_ERR, buf, buf_len, use_pri_str, chan);

	if(drop_msg == NULL || drop_msg->msg_len == 0) {
		return FALSE;
	}

	sendrc = chan->ops->send(chan, drop_msg);

	if(sendrc == IPC_OK) {
		drop_msg_num = 0;
	}else{
		FreeChildLogIPCMessage(drop_msg);
	}
	return sendrc == IPC_OK;
}
