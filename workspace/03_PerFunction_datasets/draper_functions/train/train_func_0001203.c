rdp_recv_logon_error_info(rdpRdp* rdp, STREAM* s)
{
	uint32 errorNotificationType;
	uint32 errorNotificationData;

	stream_read_uint32(s, errorNotificationType);
	stream_read_uint32(s, errorNotificationData);
}
