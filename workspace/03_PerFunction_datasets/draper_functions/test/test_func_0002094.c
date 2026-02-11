check_message_managed(void)
{
	unsigned char header[AUDIT_RMW_HEADER_SIZE];
	int hver, mver;
	uint32_t type, rlen, seq;
	char msg[MAX_AUDIT_MESSAGE_LENGTH+1];

#ifdef USE_GSSAPI
	if (USE_GSS) {
		if (recv_msg_gss (header, msg, &rlen)) {
			stop_transport();
			return -1;
		}
	} else
#endif
	if (recv_msg_tcp(header, msg, &rlen)) {
		stop_transport();
		return -1;
	}

	AUDIT_RMW_UNPACK_HEADER(header, hver, mver, type, rlen, seq);
	msg[rlen] = 0;

	if (type == AUDIT_RMW_TYPE_ENDING)
		return remote_server_ending_handler(msg);
	if (type == AUDIT_RMW_TYPE_DISKLOW)
		return remote_disk_low_handler(msg);
	if (type == AUDIT_RMW_TYPE_DISKFULL)
		return remote_disk_full_handler(msg);
	if (type == AUDIT_RMW_TYPE_DISKERROR)
		return remote_disk_error_handler(msg);
	return -1;
}
