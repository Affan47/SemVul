dm_coa_send_nak(int fd, struct rad_packet_t *req, struct sockaddr_in *addr, int err_code)
{
	struct rad_packet_t *reply;
	uint8_t RA[16];

	memcpy(RA, req->buf + 4, sizeof(RA));

	reply = rad_packet_alloc(req->code == CODE_COA_REQUEST ? CODE_COA_NAK : CODE_DISCONNECT_NAK);
	if (!reply)
		return -1;

	reply->id = req->id;

	if (err_code)
		rad_packet_add_int(reply, NULL, "Error-Cause", err_code);

	if (rad_packet_build(reply, RA)) {
		rad_packet_free(reply);
		return -1;
	}

	dm_coa_set_RA(reply, conf_dm_coa_secret);

	if (conf_verbose) {
		log_ppp_info2("send ");
		rad_packet_print(reply, NULL, log_ppp_info2);
	}

	rad_packet_send(reply, fd, addr);

	rad_packet_free(reply);

	return 0;
}
