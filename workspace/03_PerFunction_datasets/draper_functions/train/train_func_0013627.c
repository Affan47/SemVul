StreamConnection(pgsocket server_fd, Port *port)
{

	port->raddr.salen = sizeof(port->raddr.addr);
	if ((port->sock = accept(server_fd,
							 (struct sockaddr *) & port->raddr.addr,
							 &port->raddr.salen)) == PGINVALID_SOCKET)
	{
		ereport(LOG,
				(errcode_for_socket_access(),
				 errmsg("could not accept new connection: %m")));


		pg_usleep(100000L);
		return STATUS_ERROR;
	}

#ifdef SCO_ACCEPT_BUG


	if (port->raddr.addr.ss_family == 0)
		port->raddr.addr.ss_family = AF_UNIX;
#endif


	port->laddr.salen = sizeof(port->laddr.addr);
	if (getsockname(port->sock,
					(struct sockaddr *) & port->laddr.addr,
					&port->laddr.salen) < 0)
	{
		elog(LOG, "getsockname() failed: %m");
		return STATUS_ERROR;
	}


	if (!IS_AF_UNIX(port->laddr.addr.ss_family))
	{
		int			on;
#ifdef WIN32
		int			oldopt;
		int			optlen;
		int			newopt;
#endif

#ifdef	TCP_NODELAY
		on = 1;
		if (setsockopt(port->sock, IPPROTO_TCP, TCP_NODELAY,
					   (char *) &on, sizeof(on)) < 0)
		{
			elog(LOG, "setsockopt(TCP_NODELAY) failed: %m");
			return STATUS_ERROR;
		}
#endif
		on = 1;
		if (setsockopt(port->sock, SOL_SOCKET, SO_KEEPALIVE,
					   (char *) &on, sizeof(on)) < 0)
		{
			elog(LOG, "setsockopt(SO_KEEPALIVE) failed: %m");
			return STATUS_ERROR;
		}

#ifdef WIN32


		optlen = sizeof(oldopt);
		if (getsockopt(port->sock, SOL_SOCKET, SO_SNDBUF, (char *) &oldopt,
					   &optlen) < 0)
		{
			elog(LOG, "getsockopt(SO_SNDBUF) failed: %m");
			return STATUS_ERROR;
		}
		newopt = PQ_SEND_BUFFER_SIZE * 4;
		if (oldopt < newopt)
		{
			if (setsockopt(port->sock, SOL_SOCKET, SO_SNDBUF, (char *) &newopt,
						   sizeof(newopt)) < 0)
			{
				elog(LOG, "setsockopt(SO_SNDBUF) failed: %m");
				return STATUS_ERROR;
			}
		}
#endif


		(void) pq_setkeepalivesidle(tcp_keepalives_idle, port);
		(void) pq_setkeepalivesinterval(tcp_keepalives_interval, port);
		(void) pq_setkeepalivescount(tcp_keepalives_count, port);
	}

	return STATUS_OK;
}
