conn_send_sr_reply(struct drbd_connection *connection, enum drbd_state_rv retcode)
{
	struct drbd_socket *sock;
	struct p_req_state_reply *p;
	enum drbd_packet cmd = connection->agreed_pro_version < 100 ? P_STATE_CHG_REPLY : P_CONN_ST_CHG_REPLY;

	sock = &connection->meta;
	p = conn_prepare_command(connection, sock);
	if (p) {
		p->retcode = cpu_to_be32(retcode);
		conn_send_command(connection, sock, cmd, sizeof(*p), NULL, 0);
	}
}
