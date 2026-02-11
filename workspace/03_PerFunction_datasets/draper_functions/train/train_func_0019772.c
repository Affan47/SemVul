add_ipv6_miniroute ( struct net_device *netdev, struct in6_addr *address,
		     unsigned int prefix_len, struct in6_addr *router ) {
	struct ipv6_miniroute *miniroute;
	uint8_t *prefix_mask;

	DBGC ( netdev, "IPv6 add %s/%d ", inet6_ntoa ( address ), prefix_len );
	if ( router )
		DBGC ( netdev, "router %s ", inet6_ntoa ( router ) );
	DBGC ( netdev, "via %s\n", netdev->name );


	miniroute = zalloc ( sizeof ( *miniroute ) );
	if ( ! miniroute )
		return NULL;


	miniroute->netdev = netdev_get ( netdev );
	memcpy ( &miniroute->address, address, sizeof ( miniroute->address ) );
	miniroute->prefix_len = prefix_len;
	assert ( prefix_len <= ( 8 * sizeof ( miniroute->prefix_mask ) ) );
	for ( prefix_mask = miniroute->prefix_mask.s6_addr ; prefix_len >= 8 ;
	      prefix_mask++, prefix_len -= 8 ) {
		*prefix_mask = 0xff;
	}
	if ( prefix_len )
		*prefix_mask <<= ( 8 - prefix_len );
	if ( router ) {
		miniroute->has_router = 1;
		memcpy ( &miniroute->router, router,
			 sizeof ( miniroute->router ) );
	}


	if ( router ) {
		list_add_tail ( &miniroute->list, &ipv6_miniroutes );
	} else {
		list_add ( &miniroute->list, &ipv6_miniroutes );
	}

	return miniroute;
}
