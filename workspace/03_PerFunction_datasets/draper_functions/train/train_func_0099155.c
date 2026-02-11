process_reply(int reply_id, char *reply, char *reply_buf,
	      void *bin_reply, int bin_size, int *last_reply_id,
	      int *reply_slot, struct slave_state *sstate)
{

	if (*reply != '=') {
		*last_reply_id = -1;
		return true;
	}


	int cmd_id = atoi(gtp_cmd);
	if (reply_id != cmd_id) {
		*last_reply_id = reply_id;
		return true;
	}

	strncpy(reply_buf, reply, CMDS_SIZE);
	if (reply_id != *last_reply_id)
		*reply_slot = reply_count++;
	gtp_replies[*reply_slot] = reply_buf;

	if (bin_size) insert_buf(sstate, bin_reply, bin_size);

	pthread_cond_signal(&reply_cond);
	*last_reply_id = reply_id;
	return false;
}
