iscsi_conn_connect(struct iscsi_conn *conn, queue_task_t *qtask)
{
	struct iscsi_ev_context *ev_context;
	int rc;

	ev_context = iscsi_ev_context_get(conn, 0);
	if (!ev_context) {

		log_error("BUG: __session_conn_reopen could not get conn "
			  "context for recv.");
		return ENOMEM;
	}
	ev_context->data = qtask;

	rc = conn->session->t->template->ep_connect(conn, 1);
	if (rc < 0 && errno != EINPROGRESS) {
		char serv[NI_MAXSERV];

		getnameinfo((struct sockaddr *) &conn->saddr,
			    sizeof(conn->saddr),
			    conn->host, sizeof(conn->host), serv, sizeof(serv),
			    NI_NUMERICHOST|NI_NUMERICSERV);

		log_error("cannot make a connection to %s:%s (%d,%d)",
			  conn->host, serv, rc, errno);
		iscsi_ev_context_put(ev_context);
		return ENOTCONN;
	}

	iscsi_sched_ev_context(ev_context, conn, 0, EV_CONN_POLL);
	log_debug(3, "Setting login timer %p timeout %d", &conn->login_timer,
		  conn->login_timeout);
	actor_timer(&conn->login_timer, conn->login_timeout * 1000,
		    iscsi_login_timedout, qtask);
	return 0;
}
