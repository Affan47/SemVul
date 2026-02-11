l2tp_recv_HELLO(struct l2tp_conn_t *conn,
			   const struct l2tp_packet_t *pack)
{
	if (conn->state != STATE_ESTB) {
		log_tunnel(log_warn, conn, "discarding unexpected HELLO\n");

		return 0;
	}

	log_tunnel(log_debug, conn, "handling HELLO\n");

	return 0;
}
