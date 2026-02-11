isns_scn_handle(int is_accept)
{
	int err;
	struct isns_io *rx = &scn_rx;
	struct isns_hdr *hdr = (struct isns_hdr *) rx->buf;
	uint16_t function, transaction;
	char *name = NULL;

	log_error("%s %d: %d", __FUNCTION__, __LINE__, is_accept);

	if (is_accept)
		return scn_accept_connection();

	err = recv_pdu(scn_fd, rx, hdr);
	if (err) {
		if (err == -EAGAIN)
			return err;
		log_debug(1, "%s %d: close connection %d", __FUNCTION__, __LINE__,
			  scn_fd);
		close(scn_fd);
		scn_fd = 0;
		isns_set_fd(isns_fd, scn_listen_fd, 0);
		return err;
	}

	function = ntohs(hdr->function);
	transaction = ntohs(hdr->transaction);

	switch (function) {
	case ISNS_FUNC_SCN:
		name = print_scn_pdu(hdr);
		break;
	default:
		print_unknown_pdu(hdr);
	}

	if (name) {
		send_scn_rsp(name, transaction);
		isns_attr_query(name);
	}

	return 0;
}
