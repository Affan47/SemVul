ns_client_isself(dns_view_t *myview, dns_tsigkey_t *mykey,
		 isc_sockaddr_t *srcaddr, isc_sockaddr_t *dstaddr,
		 dns_rdataclass_t rdclass, void *arg)
{
	dns_view_t *view;
	dns_tsigkey_t *key = NULL;
	dns_name_t *tsig = NULL;
	isc_netaddr_t netsrc;
	isc_netaddr_t netdst;

	UNUSED(arg);


	if (ns_g_server->interfacemgr == NULL)
		return (ISC_TRUE);

	if (!ns_interfacemgr_listeningon(ns_g_server->interfacemgr, dstaddr))
		return (ISC_FALSE);

	isc_netaddr_fromsockaddr(&netsrc, srcaddr);
	isc_netaddr_fromsockaddr(&netdst, dstaddr);

	for (view = ISC_LIST_HEAD(ns_g_server->viewlist);
	     view != NULL;
	     view = ISC_LIST_NEXT(view, link)) {

		if (view->matchrecursiveonly)
			continue;

		if (rdclass != view->rdclass)
			continue;

		if (mykey != NULL) {
			isc_boolean_t match;
			isc_result_t result;

			result = dns_view_gettsig(view, &mykey->name, &key);
			if (result != ISC_R_SUCCESS)
				continue;
			match = dst_key_compare(mykey->key, key->key);
			dns_tsigkey_detach(&key);
			if (!match)
				continue;
			tsig = dns_tsigkey_identity(mykey);
		}

		if (allowed(&netsrc, tsig, NULL, 0, NULL,
			    view->matchclients) &&
		    allowed(&netdst, tsig, NULL, 0, NULL,
			    view->matchdestinations))
			break;
	}
	return (ISC_TF(view == myview));
}
