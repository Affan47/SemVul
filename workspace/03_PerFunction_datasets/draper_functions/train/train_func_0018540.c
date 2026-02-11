ap_get_single_string_command(int session, int32_t cmd, char *str, int maxlen)
{
	int fd;
	ap_message_t *msg, *reply;
	char *result;

	if (!str)
		return 0;

	str[0] = 0;


	fd = ap_connect_session(session);
	if (fd < 0)
		return 0;
	msg = ap_message_new();
	msg->header.cmd = cmd;

	ap_message_send(fd, msg);
	ap_message_delete(msg);
	msg = NULL;

	reply = ap_message_receive(fd);
	close(fd);

	if ((result = ap_message_find_string(reply, "string"))) {
		if (strlen(result) > (size_t)maxlen) {
			strncpy(str, result, maxlen-1);
			str[maxlen] = 0;
		} else
			strcpy(str, result);
		ap_message_delete(reply);
		return 1;
	}
	ap_message_delete(reply);
	return 0;
}
