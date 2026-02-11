ap_get_speed(int session, float *val)
{
	int fd;
	ap_message_t *msg, *reply;
	float *result;

	fd = ap_connect_session(session);
	if (fd < 0)
		return 0;
	msg = ap_message_new();
	msg->header.cmd = AP_GET_SPEED;
	ap_message_send(fd, msg);
	ap_message_delete(msg);
	msg = NULL;

	reply = ap_message_receive(fd);
	close(fd);

	if ((result = ap_message_find_float(reply, "speed"))) {
		*val = *result;
		ap_message_delete(reply);
		return 1;
	}
	ap_message_delete(reply);
	return 0;
}
