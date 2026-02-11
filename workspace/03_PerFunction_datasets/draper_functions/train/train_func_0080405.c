tds_free_msg(TDSMESSAGE * message)
{
	if (message) {
		message->priv_msg_type = 0;
		message->msgno = 0;
		message->state = 0;
		message->severity = 0;
		message->line_number = 0;
		if (message->message)
			TDS_ZERO_FREE(message->message);
		if (message->server)
			TDS_ZERO_FREE(message->server);
		if (message->proc_name)
			TDS_ZERO_FREE(message->proc_name);
		if (message->sql_state)
			TDS_ZERO_FREE(message->sql_state);
	}
}
