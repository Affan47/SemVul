l2tp_recv_SCCCN(struct l2tp_conn_t *conn,
			   const struct l2tp_packet_t *pack)
{
	const struct l2tp_attr_t *attr = NULL;
	const struct l2tp_attr_t *challenge_resp = NULL;
	char host_addr[17];

	if (conn->state != STATE_WAIT_SCCCN) {
		log_tunnel(log_warn, conn, "discarding unexpected SCCCN\n");
		return 0;
	}

	log_tunnel(log_info2, conn, "handling SCCCN\n");

	list_for_each_entry(attr, &pack->attrs, entry) {
		switch (attr->attr->id) {
		case Message_Type:
		case Random_Vector:
			break;
		case Challenge_Response:
			challenge_resp = attr;
			break;
		default:
			if (attr->M) {
				log_tunnel(log_error, conn,
					   "impossible to handle SCCCN:"
					   " unknown mandatory attribute type %i,"
					   " disconnecting tunnel\n",
					   attr->attr->id);
				l2tp_tunnel_disconnect(conn, 2, 8);
				return -1;
			}
		}
	}

	if (l2tp_tunnel_checkchallresp(Message_Type_Start_Ctrl_Conn_Connected,
				       conn, challenge_resp) < 0) {
		log_tunnel(log_error, conn, "impossible to handle SCCCN:"
			   " checking Challenge Response failed,"
			   " disconnecting tunnel\n");
		l2tp_tunnel_disconnect(conn, 4, 0);
		return -1;
	}
	l2tp_tunnel_storechall(conn, NULL);

	if (l2tp_tunnel_connect(conn) < 0) {
		log_tunnel(log_error, conn, "impossible to handle SCCCN:"
			   " connecting tunnel failed,"
			   " disconnecting tunnel\n");
		l2tp_tunnel_disconnect(conn, 2, 0);
		return -1;
	}

	u_inet_ntoa(conn->host_addr.sin_addr.s_addr, host_addr);
	log_tunnel(log_info1, conn, "established at %s:%hu\n",
		   host_addr, ntohs(conn->host_addr.sin_port));

	return 0;
}
