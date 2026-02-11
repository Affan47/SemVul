ns_lwdclient_sendreply(ns_lwdclient_t *client, isc_region_t *r) {
	struct in6_pktinfo *pktinfo;
	ns_lwdclientmgr_t *cm = client->clientmgr;

	if (client->pktinfo_valid)
		pktinfo = &client->pktinfo;
	else
		pktinfo = NULL;
	return (isc_socket_sendto(cm->sock, r, cm->task, ns_lwdclient_send,
				  client, &client->address, pktinfo));
}
