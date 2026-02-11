l2tp_recv_ICRQ(struct l2tp_conn_t *conn,
			  const struct l2tp_packet_t *pack)
{
	const struct l2tp_attr_t *attr;
	const struct l2tp_attr_t *assigned_sid = NULL;
	const struct l2tp_attr_t *unknown_attr = NULL;
	struct l2tp_sess_t *sess = NULL;
	uint16_t peer_sid = 0;
	uint16_t sid = 0;
	uint16_t res = 0;
	uint16_t err = 0;

	if (conn->state != STATE_ESTB && conn->lns_mode) {
		log_tunnel(log_warn, conn, "discarding unexpected ICRQ\n");
		return 0;
	}

	if (ap_shutdown) {
		log_tunnel(log_warn, conn, "shutdown in progress,"
			   " discarding ICRQ\n");
		return 0;
	}

	if (triton_module_loaded("connlimit")
	    && connlimit_check(cl_key_from_ipv4(conn->peer_addr.sin_addr.s_addr))) {
		log_tunnel(log_warn, conn, "connection limits reached,"
			   " discarding ICRQ\n");
		return 0;
	}

	log_tunnel(log_info2, conn, "handling ICRQ\n");

	list_for_each_entry(attr, &pack->attrs, entry) {
		switch(attr->attr->id) {
			case Assigned_Session_ID:
				assigned_sid = attr;
				break;
			case Message_Type:
			case Random_Vector:
			case Call_Serial_Number:
			case Bearer_Type:
			case Calling_Number:
			case Called_Number:
			case Sub_Address:
			case Physical_Channel_ID:
				break;
			default:
				if (attr->M)
					unknown_attr = attr;
				else
					log_tunnel(log_warn, conn,
						   "discarding unknown attribute type"
						   " %i in ICRQ\n", attr->attr->id);
				break;
		}
	}

	if (!assigned_sid) {
		log_tunnel(log_error, conn, "impossible to handle ICRQ:"
			   " no Assigned Session ID present in message,"
			   " disconnecting session\n");
		res = 2;
		err = 6;
		goto out_reject;
	}

	peer_sid = assigned_sid->val.uint16;

	sess = l2tp_tunnel_alloc_session(conn);
	if (sess == NULL) {
		log_tunnel(log_error, conn, "impossible to handle ICRQ:"
			   " session allocation failed,"
			   " disconnecting session\n");
		res = 2;
		err = 4;
		goto out_reject;
	}

	sess->peer_sid = peer_sid;
	sid = sess->sid;

	if (unknown_attr) {
		log_tunnel(log_error, conn, "impossible to handle ICRQ:"
			   " unknown mandatory attribute type %i,"
			   " disconnecting session\n",
			   unknown_attr->attr->id);
		res = 2;
		err = 8;
		goto out_reject;
	}

	if (l2tp_session_incall_reply(sess) < 0) {
		log_tunnel(log_error, conn, "impossible to handle ICRQ:"
			   " starting session failed,"
			   " disconnecting session\n");
		res = 2;
		err = 4;
		goto out_reject;
	}

	log_tunnel(log_info1, conn, "new session %hu-%hu created following"
		   " reception of ICRQ\n", sid, peer_sid);

	return 0;

out_reject:
	if (l2tp_tunnel_send_CDN(sid, peer_sid, res, err) < 0)
		log_tunnel(log_warn, conn,
			   "impossible to reject ICRQ:"
			   " sending CDN failed\n");
	if (sess)
		l2tp_session_free(sess);

	return -1;
}
