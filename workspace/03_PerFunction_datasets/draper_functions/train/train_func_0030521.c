session_conn_shutdown(iscsi_conn_t *conn, queue_task_t *qtask,
		      int err)
{
	iscsi_session_t *session = conn->session;

	log_debug(2, "disconnect conn");

	if (session->t->template->ep_disconnect)
		session->t->template->ep_disconnect(conn);

	if (session->id == -1)
		goto cleanup;

	if (!iscsi_sysfs_session_has_leadconn(session->id))
		goto cleanup;

	if (conn->state == ISCSI_CONN_STATE_IN_LOGIN ||
	    conn->state == ISCSI_CONN_STATE_IN_LOGOUT ||
	    conn->state == ISCSI_CONN_STATE_LOGGED_IN) {
		log_debug(2, "stop conn (conn state %d)", conn->state);
		if (ipc->stop_conn(session->t->handle, session->id,
				   conn->id, STOP_CONN_TERM)) {
			log_error("can't stop connection %d:%d (%d)",
				  session->id, conn->id, errno);
			return ISCSI_ERR_INTERNAL;
		}
	}

	log_debug(2, "kdestroy conn");
	if (ipc->destroy_conn(session->t->handle, session->id,
		conn->id)) {
		log_error("can not safely destroy connection %d", conn->id);
		return ISCSI_ERR_INTERNAL;
	}

cleanup:
	if (session->id != -1) {
		log_debug(2, "kdestroy session %u", session->id);
		session->r_stage = R_STAGE_SESSION_DESTOYED;
		if (ipc->destroy_session(session->t->handle, session->id)) {
			log_error("can not safely destroy session %d",
				  session->id);
			return ISCSI_ERR_INTERNAL;
		}
	}

	log_warning("Connection%d:%d to [target: %s, portal: %s,%d] "
		    "through [iface: %s] is shutdown.",
		    session->id, conn->id, session->nrec.name,
		    session->nrec.conn[conn->id].address,
		    session->nrec.conn[conn->id].port,
		    session->nrec.iface.name);

	mgmt_ipc_write_rsp(qtask, err);
	conn_delete_timers(conn);
	__session_destroy(session);
	return ISCSI_SUCCESS;
}
