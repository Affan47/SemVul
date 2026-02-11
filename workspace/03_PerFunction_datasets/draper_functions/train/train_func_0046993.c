conn_fd_handler(int fd)
{
	struct connection *conn = fdtab[fd].owner;
	unsigned int flags;

	if (unlikely(!conn))
		return 0;

	conn_refresh_polling_flags(conn);
	flags = conn->flags & ~CO_FL_ERROR;

 process_handshake:


	while (unlikely(conn->flags & (CO_FL_HANDSHAKE | CO_FL_ERROR))) {
		if (unlikely(conn->flags & CO_FL_ERROR))
			goto leave;

		if (conn->flags & CO_FL_ACCEPT_PROXY)
			if (!conn_recv_proxy(conn, CO_FL_ACCEPT_PROXY))
				goto leave;

		if (conn->flags & CO_FL_SEND_PROXY)
			if (!conn_si_send_proxy(conn, CO_FL_SEND_PROXY))
				goto leave;
#ifdef USE_OPENSSL
		if (conn->flags & CO_FL_SSL_WAIT_HS)
			if (!ssl_sock_handshake(conn, CO_FL_SSL_WAIT_HS))
				goto leave;
#endif
	}


	if (!(conn->flags & CO_FL_POLL_SOCK))
		__conn_sock_stop_both(conn);


	if ((conn->flags & CO_FL_INIT_DATA) && conn->data->init(conn) < 0)
		return 0;


	if (conn->xprt && fd_recv_ready(fd) &&
	    ((conn->flags & (CO_FL_DATA_RD_ENA|CO_FL_WAIT_ROOM|CO_FL_ERROR|CO_FL_HANDSHAKE)) == CO_FL_DATA_RD_ENA)) {


		flags = CO_FL_WAIT_L4_CONN | CO_FL_CONNECTED;
		conn->data->recv(conn);
	}

	if (conn->xprt && fd_send_ready(fd) &&
	    ((conn->flags & (CO_FL_DATA_WR_ENA|CO_FL_WAIT_DATA|CO_FL_ERROR|CO_FL_HANDSHAKE)) == CO_FL_DATA_WR_ENA)) {


		flags = CO_FL_WAIT_L4_CONN | CO_FL_CONNECTED;
		conn->data->send(conn);
	}


	if (unlikely(conn->flags & (CO_FL_HANDSHAKE | CO_FL_ERROR)))
		goto process_handshake;

	if (unlikely(conn->flags & CO_FL_WAIT_L4_CONN)) {


		if (!tcp_connect_probe(conn))
			goto leave;
	}

 leave:


	if ((conn->flags & CO_FL_WAKE_DATA) &&
	    ((conn->flags ^ flags) & CO_FL_CONN_STATE) &&
	    conn->data->wake(conn) < 0)
		return 0;


	if (unlikely(!(conn->flags & (CO_FL_WAIT_L4_CONN | CO_FL_WAIT_L6_CONN | CO_FL_CONNECTED))))
		conn->flags |= CO_FL_CONNECTED;


	fdtab[fd].ev &= FD_POLL_STICKY;


	conn_cond_update_polling(conn);
	return 0;
}
