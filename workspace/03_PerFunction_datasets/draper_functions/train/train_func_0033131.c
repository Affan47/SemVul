__session_conn_reopen(iscsi_conn_t *conn, queue_task_t *qtask, int do_stop,
		      int redirected)
{
	iscsi_session_t *session = conn->session;
	uint32_t delay;

	log_debug(1, "re-opening session %d (reopen_cnt %d)", session->id,
			session->reopen_cnt);

	qtask->conn = conn;


	iscsi_flush_context_pool(session);
	conn_delete_timers(conn);
	conn->state = ISCSI_CONN_STATE_XPT_WAIT;

	conn->session->t->template->ep_disconnect(conn);
	if (do_stop) {

		if (ipc->stop_conn(session->t->handle, session->id,
				   conn->id, do_stop)) {
			log_error("can't stop connection %d:%d (%d)",
				  session->id, conn->id, errno);
			delay = ISCSI_INTERNAL_ERR_REOPEN_DELAY;
			goto queue_reopen;
		}
		log_debug(3, "connection %d:%d is stopped for recovery",
			  session->id, conn->id);
	}

	if (!redirected) {
		delay = session->def_time2wait;
		session->def_time2wait = 0;
		if (delay)
			goto queue_reopen;
	}

	if (!redirected)
		session->reopen_cnt++;

	if (iscsi_conn_connect(conn, qtask)) {
		delay = ISCSI_CONN_ERR_REOPEN_DELAY;
		goto queue_reopen;
	}
	return;

queue_reopen:
	log_debug(4, "Waiting %u seconds before trying to reconnect.\n", delay);
	queue_delayed_reopen(qtask, delay);
}
