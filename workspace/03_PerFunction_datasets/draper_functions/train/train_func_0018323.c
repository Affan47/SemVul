ipmiv2_lan_ping(struct ipmi_intf * intf)
{
	struct asf_hdr asf_ping = {
		.iana	= htonl(ASF_RMCP_IANA),
		.type	= ASF_TYPE_PING,
	};
	struct rmcp_hdr rmcp_ping = {
		.ver	= RMCP_VERSION_1,
		.class	= RMCP_CLASS_ASF,
		.seq	= 0xff,
	};
	uint8_t * data;
	int len = sizeof(rmcp_ping) + sizeof(asf_ping);
	int rv;

	data = malloc(len);
	if (data == NULL) {
		lprintf(LOG_ERR, "ipmitool: malloc failure");
		return -1;
	}
	memset(data, 0, len);
	memcpy(data, &rmcp_ping, sizeof(rmcp_ping));
	memcpy(data+sizeof(rmcp_ping), &asf_ping, sizeof(asf_ping));

	lprintf(LOG_DEBUG, "Sending IPMI/RMCP presence ping packet");

	rv = ipmi_lan_send_packet(intf, data, len);

	free(data);
	data = NULL;

	if (rv < 0) {
		lprintf(LOG_ERR, "Unable to send IPMI presence ping packet");
		return -1;
	}

	if (ipmi_lan_poll_recv(intf) == 0)
		return 0;

	return 1;
}
