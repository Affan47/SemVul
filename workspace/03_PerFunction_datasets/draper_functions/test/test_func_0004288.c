dcc_get_listen(GET_DCC_REC *dcc)
{
	GIOChannel *handle;
	IPADDR addr;
	int port;


	handle = net_accept(dcc->handle, &addr, &port);
	if (handle == NULL)
		return;

	net_disconnect(dcc->handle);
	g_source_remove(dcc->tagconn);
	dcc->tagconn = -1;

	dcc->starttime = time(NULL);
	dcc->handle = handle;
	memcpy(&dcc->addr, &addr, sizeof(IPADDR));
	net_ip2host(&dcc->addr, dcc->addrstr);
	dcc->port = port;

	dcc->tagconn = g_input_add(handle, G_INPUT_READ | G_INPUT_WRITE,
				   (GInputFunction) sig_dccget_connected, dcc);
}
