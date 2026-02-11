generate_reply(ns_lwdclient_t *client) {
	isc_result_t result;
	int lwres;
	isc_region_t r;
	lwres_buffer_t lwb;
	ns_lwdclientmgr_t *cm;

	cm = client->clientmgr;
	lwb.base = NULL;

	ns_lwdclient_log(50, "generating gabn reply for client %p", client);


	if (client->find == client->v4find || client->find == client->v6find)
		client->find = NULL;
	else
		if (client->find != NULL)
			dns_adb_destroyfind(&client->find);


	if (NEED_V6(client) && client->v4find != NULL)
		client->v6find = client->v4find;


	LWRES_LIST_INIT(client->gabn.addrs);
	if (client->v4find != NULL)
		setup_addresses(client, client->v4find, DNS_ADBFIND_INET);
	if (client->v6find != NULL)
		setup_addresses(client, client->v6find, DNS_ADBFIND_INET6);


	if (client->gabn.naddrs == 0) {
		do {
			result = ns_lwsearchctx_next(&client->searchctx);
			if (result == ISC_R_SUCCESS) {
				cleanup_gabn(client);
				result = start_find(client);
				if (result == ISC_R_SUCCESS)
					return;
			}
		} while (result == ISC_R_SUCCESS);
	}


	client->pkt.recvlength = LWRES_RECVLENGTH;
	client->pkt.authtype = 0;
	client->pkt.authlength = 0;


	if (client->gabn.naddrs != 0)
		client->pkt.result = LWRES_R_SUCCESS;
	else
		client->pkt.result = LWRES_R_NOTFOUND;

	sort_addresses(client);

	lwres = lwres_gabnresponse_render(cm->lwctx, &client->gabn,
					  &client->pkt, &lwb);
	if (lwres != LWRES_R_SUCCESS)
		goto out;

	r.base = lwb.base;
	r.length = lwb.used;
	client->sendbuf = r.base;
	client->sendlength = r.length;
	result = ns_lwdclient_sendreply(client, &r);
	if (result != ISC_R_SUCCESS)
		goto out;

	NS_LWDCLIENT_SETSEND(client);


	cleanup_gabn(client);

	return;

 out:
	cleanup_gabn(client);

	if (lwb.base != NULL)
		lwres_context_freemem(client->clientmgr->lwctx,
				      lwb.base, lwb.length);

	ns_lwdclient_errorpktsend(client, LWRES_R_FAILURE);
}
