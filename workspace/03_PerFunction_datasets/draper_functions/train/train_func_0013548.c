setup_query_sortlist(ns_client_t *client) {
	isc_netaddr_t netaddr;
	dns_rdatasetorderfunc_t order = NULL;
	const void *order_arg = NULL;

	isc_netaddr_fromsockaddr(&netaddr, &client->peeraddr);
	switch (ns_sortlist_setup(client->view->sortlist,
			       &netaddr, &order_arg)) {
	case NS_SORTLISTTYPE_1ELEMENT:
		order = query_sortlist_order_1element;
		break;
	case NS_SORTLISTTYPE_2ELEMENT:
		order = query_sortlist_order_2element;
		break;
	case NS_SORTLISTTYPE_NONE:
		order = NULL;
		break;
	default:
		INSIST(0);
		break;
	}
	dns_message_setsortorder(client->message, order, order_arg);
}
