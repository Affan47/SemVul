set_nameserver(char *opt) {
	isc_result_t result;
	isc_sockaddr_t sockaddrs[DIG_MAX_ADDRESSES];
	isc_netaddr_t netaddr;
	int count, i;
	dig_server_t *srv;
	char tmp[ISC_NETADDR_FORMATSIZE];

	if (opt == NULL)
		return;

	result = bind9_getaddresses(opt, 0, sockaddrs,
				    DIG_MAX_ADDRESSES, &count);
	if (result != ISC_R_SUCCESS)
		fatal("couldn't get address for '%s': %s",
		      opt, isc_result_totext(result));

	flush_server_list();

	for (i = 0; i < count; i++) {
		isc_netaddr_fromsockaddr(&netaddr, &sockaddrs[i]);
		isc_netaddr_format(&netaddr, tmp, sizeof(tmp));
		srv = make_server(tmp, opt);
		if (srv == NULL)
			fatal("memory allocation failure");
		ISC_LIST_APPEND(server_list, srv, link);
	}
}
