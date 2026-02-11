net_backend_process_select(struct net_backend* data, int res)
{
	int n, found;
	struct net_backend_select* backend = (struct net_backend_select*) data;
	for (n = 0, found = 0; found < res && n < backend->maxfd; n++)
	{
		struct net_connection_select* con = backend->conns[n];
		if (con)
		{
			int ev = 0;
			if (FD_ISSET(con->sd, &backend->rfds)) ev |= NET_EVENT_READ;
			if (FD_ISSET(con->sd, &backend->wfds)) ev |= NET_EVENT_WRITE;

			if (ev)
			{
				net_con_callback((struct net_connection*) con, ev);
				found++;
			}
		}
	}
}
