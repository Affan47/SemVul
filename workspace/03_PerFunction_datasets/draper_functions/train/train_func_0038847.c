l2tp_tunnel_send_CDN(uint16_t sid, uint16_t peer_sid,
				uint16_t res, uint16_t err)
{
	struct l2tp_packet_t *pack = NULL;
	struct l2tp_avp_result_code rc = {htons(res), htons(err)};
	struct l2tp_conn_t *conn = l2tp_tunnel_self();

	log_tunnel(log_info2, conn, "sending CDN (res: %hu, err: %hu)\n",
		   res, err);

	pack = l2tp_packet_alloc(2, Message_Type_Call_Disconnect_Notify,
				 &conn->peer_addr, conn->hide_avps,
				 conn->secret, conn->secret_len);
	if (pack == NULL) {
		log_tunnel(log_error, conn, "impossible to send CDN:"
			   " packet allocation failed\n");
		goto out_err;
	}
	if (l2tp_packet_add_int16(pack, Assigned_Session_ID, sid, 1) < 0) {
		log_tunnel(log_error, conn, "impossible to send CDN:"
			   " adding data to packet failed\n");
		goto out_err;
	}
	if (l2tp_packet_add_octets(pack, Result_Code, (uint8_t *)&rc,
				   sizeof(rc), 1) < 0) {
		log_tunnel(log_error, conn, "impossible to send CDN:"
			   " adding data to packet failed\n");
		goto out_err;
	}

	pack->hdr.sid = htons(peer_sid);

	l2tp_tunnel_send(conn, pack);

	return 0;

out_err:
	if (pack)
		l2tp_packet_free(pack);
	return -1;
}
