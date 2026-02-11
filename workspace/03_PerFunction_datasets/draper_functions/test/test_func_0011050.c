ap_cmd_set_int(int session, int32_t cmd, int val)
{
	int fd;
	ap_message_t *msg, *reply;
	int32_t *result;

	fd = ap_connect_session(session);
	if (fd < 0)
		return 0;
	msg = ap_message_new();
	msg->header.cmd = cmd;
	ap_message_add_int32(msg, "int", val);

	ap_message_send(fd, msg);
	ap_message_delete(msg);
	msg = NULL;

	reply = ap_message_receive(fd);
	close(fd);

	if ((result = ap_message_find_int32(reply, "ack"))) {
		ap_message_delete(reply);
		return 1;
	}
	ap_message_delete(reply);
	return 0;
}
