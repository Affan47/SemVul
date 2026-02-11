l2tp_tunnel_disconnect_push(struct l2tp_conn_t *conn,
				       uint16_t res, uint16_t err)
{
	if (l2tp_tunnel_disconnect(conn, res, err) < 0)
		return -1;

	if (l2tp_tunnel_push_sendqueue(conn) < 0) {
		log_tunnel(log_error, conn,
			   "impossible to notify peer of tunnel disconnection:"
			   " transmitting messages from send queue failed,"
			   " deleting tunnel anyway\n");
		l2tp_tunnel_free(conn);

		return -1;
	}

	return 0;
}
