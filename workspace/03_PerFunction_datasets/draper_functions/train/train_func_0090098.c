client_sendpkg(ns_client_t *client, isc_buffer_t *buffer) {
	struct in6_pktinfo *pktinfo;
	isc_result_t result;
	isc_region_t r;
	isc_sockaddr_t *address;
	isc_socket_t *socket;
	isc_netaddr_t netaddr;
	int match;
	unsigned int sockflags = ISC_SOCKFLAG_IMMEDIATE;

	if (TCP_CLIENT(client)) {
		socket = client->tcpsocket;
		address = NULL;
	} else {
		socket = client->udpsocket;
		address = &client->peeraddr;

		isc_netaddr_fromsockaddr(&netaddr, &client->peeraddr);
		if (ns_g_server->blackholeacl != NULL &&
		    dns_acl_match(&netaddr, NULL,
				  ns_g_server->blackholeacl,
				  &ns_g_server->aclenv,
				  &match, NULL) == ISC_R_SUCCESS &&
		    match > 0)
			return (DNS_R_BLACKHOLED);
		sockflags |= ISC_SOCKFLAG_NORETRY;
	}

	if ((client->attributes & NS_CLIENTATTR_PKTINFO) != 0 &&
	    (client->attributes & NS_CLIENTATTR_MULTICAST) == 0)
		pktinfo = &client->pktinfo;
	else
		pktinfo = NULL;

	isc_buffer_usedregion(buffer, &r);

	CTRACE("sendto");

	result = isc_socket_sendto2(socket, &r, client->task,
				    address, pktinfo,
				    client->sendevent, sockflags);
	if (result == ISC_R_SUCCESS || result == ISC_R_INPROGRESS) {
		client->nsends++;
		if (result == ISC_R_SUCCESS)
			client_senddone(client->task,
					(isc_event_t *)client->sendevent);
		result = ISC_R_SUCCESS;
	}
	return (result);
}
