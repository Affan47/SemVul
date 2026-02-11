iterate_targets(iscsi_session_t *session, uint32_t ttt)
{
	char data[64];
	struct iscsi_text text;
	struct iscsi_hdr *pdu = (struct iscsi_hdr *) &text;

	memset(&text, 0, sizeof (text));
	memset(data, 0, sizeof (data));


	if (!iscsi_make_text_pdu(session, pdu, data, sizeof (data))) {
		log_error("failed to make an empty text PDU");
		return 0;
	}

	text.ttt = ttt;
	text.flags = ISCSI_FLAG_CMD_FINAL;

	if (!iscsi_io_send_pdu(&session->conn[0], pdu, ISCSI_DIGEST_NONE, data,
		    ISCSI_DIGEST_NONE, session->conn[0].active_timeout)) {
		log_error("failed to send empty text PDU");
		return 0;
	}

	return 1;
}
