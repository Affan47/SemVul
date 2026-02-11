l2tp_send_CDN(struct l2tp_sess_t *sess, uint16_t res, uint16_t err)
{
	struct l2tp_packet_t *pack = NULL;
	struct l2tp_avp_result_code rc = {htons(res), htons(err)};

	log_session(log_info2, sess, "sending CDN (res: %hu, err: %hu)\n",
		    res, err);

	pack = l2tp_packet_alloc(2, Message_Type_Call_Disconnect_Notify,
				 &sess->paren_conn->peer_addr, sess->hide_avps,
				 sess->paren_conn->secret,
				 sess->paren_conn->secret_len);
	if (pack == NULL) {
		log_session(log_error, sess, "impossible to send CDN:"
			    " packet allocation failed\n");
		goto out_err;
	}
	if (l2tp_packet_add_int16(pack, Assigned_Session_ID,
				  sess->sid, 1) < 0) {
		log_session(log_error, sess, "impossible to send CDN:"
			    " adding data to packet failed\n");
		goto out_err;
	}
	if (l2tp_packet_add_octets(pack, Result_Code, (uint8_t *)&rc,
				   sizeof(rc), 1) < 0) {
		log_session(log_error, sess, "impossible to send CDN:"
			    " adding data to packet failed\n");
		goto out_err;
	}

	l2tp_session_send(sess, pack);

	return 0;

out_err:
	if (pack)
		l2tp_packet_free(pack);
	return -1;
}
