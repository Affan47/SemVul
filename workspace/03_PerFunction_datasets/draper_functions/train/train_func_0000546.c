l2tp_send_OCCN(struct l2tp_sess_t *sess)
{
	struct l2tp_packet_t *pack = NULL;

	log_session(log_info2, sess, "sending OCCN\n");

	pack = l2tp_packet_alloc(2, Message_Type_Outgoing_Call_Connected,
				 &sess->paren_conn->peer_addr, sess->hide_avps,
				 sess->paren_conn->secret,
				 sess->paren_conn->secret_len);
	if (pack == NULL) {
		log_session(log_error, sess, "impossible to send OCCN:"
			    " packet allocation failed\n");
		return -1;
	}

	if (l2tp_packet_add_int32(pack, TX_Speed, 1000, 1) < 0) {
		log_session(log_error, sess, "impossible to send OCCN:"
			    " adding data to packet failed\n");
		goto out_err;
	}
	if (l2tp_packet_add_int32(pack, Framing_Type, 3, 1) < 0) {
		log_session(log_error, sess, "impossible to send OCCN:"
			    " adding data to packet failed\n");
		goto out_err;
	}
	if (sess->send_seq &&
	    l2tp_packet_add_octets(pack, Sequencing_Required, NULL, 0, 1) < 0) {
		log_session(log_error, sess, "impossible to send OCCN:"
			    " adding data to packet failed\n");
		goto out_err;
	}

	l2tp_session_send(sess, pack);

	return 0;

out_err:
	l2tp_packet_free(pack);
	return -1;
}
