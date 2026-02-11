rdp_recv_save_session_info(rdpRdp* rdp, STREAM* s)
{
	uint32 infoType;

	stream_read_uint32(s, infoType);

	printf("%s\n", INFO_TYPE_LOGON_STRINGS[infoType]);

	switch (infoType)
	{
		case INFO_TYPE_LOGON:
			rdp_recv_logon_info_v1(rdp, s);
			break;

		case INFO_TYPE_LOGON_LONG:
			rdp_recv_logon_info_v2(rdp, s);
			break;

		case INFO_TYPE_LOGON_PLAIN_NOTIFY:
			rdp_recv_logon_plain_notify(rdp, s);
			break;

		case INFO_TYPE_LOGON_EXTENDED_INF:
			rdp_recv_logon_info_extended(rdp, s);
			break;

		default:
			break;
	}
}
