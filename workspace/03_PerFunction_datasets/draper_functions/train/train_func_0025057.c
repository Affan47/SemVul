init_gnba(ns_lwdclient_t *client) {
	int i;


	for (i = 0; i < LWRES_MAX_ALIASES; i++) {
		client->aliases[i] = NULL;
		client->aliaslen[i] = 0;
	}
	for (i = 0; i < LWRES_MAX_ADDRS; i++) {
		client->addrs[i].family = 0;
		client->addrs[i].length = 0;
		memset(client->addrs[i].address, 0, LWRES_ADDR_MAXLEN);
		LWRES_LINK_INIT(&client->addrs[i], link);
	}

	client->gnba.naliases = 0;
	client->gnba.realname = NULL;
	client->gnba.aliases = client->aliases;
	client->gnba.realnamelen = 0;
	client->gnba.aliaslen = client->aliaslen;
	client->gnba.base = NULL;
	client->gnba.baselen = 0;
	isc_buffer_init(&client->recv_buffer, client->buffer, LWRES_RECVLENGTH);
}
