ndp_resolve ( struct net_device *netdev, struct in6_addr *dest,
		  struct in6_addr *src, void *dest_ll_addr ) {
	struct ll_protocol *ll_protocol = netdev->ll_protocol;
	struct ndp_entry *ndp;
	int rc;

	ndp = ndp_find_entry ( dest );

	if ( ndp && ndp->state == NDP_STATE_REACHABLE ) {
		DBG ( "Neighbour cache hit: IP6 %s => %s %s\n",
		      inet6_ntoa ( *dest ), ll_protocol->name,
		      ll_protocol->ntoa ( ndp->ll_addr ) );
		memcpy ( dest_ll_addr, ndp->ll_addr, ll_protocol->ll_addr_len );
		return 0;
	}


	if ( ndp ) {
		DBG ( "Awaiting neighbour advertisement\n" );


		return -ENOENT;
	}
	DBG ( "Neighbour cache miss: IP6 %s\n", inet6_ntoa ( *dest ) );


	add_ndp_entry ( netdev, dest, NULL, NDP_STATE_INCOMPLETE );


	if ( ( rc = icmp6_send_solicit ( netdev, src, dest ) ) != 0 ) {
		return rc;
	}
	return -ENOENT;
}
