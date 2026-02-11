l2tp_tunnel_disconnect(struct l2tp_conn_t *conn,
				  uint16_t res, uint16_t err)
{
	switch (conn->state) {
	case STATE_INIT:
	case STATE_WAIT_SCCRP:
	case STATE_WAIT_SCCCN:
		__sync_sub_and_fetch(&stat_conn_starting, 1);
		__sync_add_and_fetch(&stat_conn_finishing, 1);
		break;
	case STATE_ESTB:
		__sync_sub_and_fetch(&stat_conn_active, 1);
		__sync_add_and_fetch(&stat_conn_finishing, 1);
		break;
	case STATE_FIN:
	case STATE_FIN_WAIT:
	case STATE_CLOSE:
		return 0;
	default:
		log_tunnel(log_error, conn,
			   "impossible to disconnect tunnel:"
			   " invalid state %i\n",
			   conn->state);
		return 0;
	}


	l2tp_tunnel_clear_sendqueue(conn);

	if (l2tp_send_StopCCN(conn, res, err) < 0) {
		log_tunnel(log_error, conn,
			   "impossible to notify peer of tunnel disconnection:"
			   " sending StopCCN failed,"
			   " deleting tunnel anyway\n");

		conn->state = STATE_FIN;
		l2tp_tunnel_free(conn);

		return -1;
	}

	conn->state = STATE_FIN;

	if (conn->timeout_timer.tpd)
		triton_timer_del(&conn->timeout_timer);
	if (conn->hello_timer.tpd)
		triton_timer_del(&conn->hello_timer);

	if (conn->sessions)
		l2tp_tunnel_free_sessions(conn);

	return 0;
}
