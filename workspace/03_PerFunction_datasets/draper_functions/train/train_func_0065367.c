ndp_tx_router_solicitation ( struct net_device *netdev ) {
	struct ndp_router_solicitation_header rsol;
	struct sockaddr_in6 sin6_dest;
	int rc;


	memset ( &sin6_dest, 0, sizeof ( sin6_dest ) );
	sin6_dest.sin6_family = AF_INET6;
	sin6_dest.sin6_scope_id = netdev->index;
	ipv6_all_routers ( &sin6_dest.sin6_addr );


	memset ( &rsol, 0, sizeof ( rsol ) );
	rsol.icmp.type = ICMPV6_ROUTER_SOLICITATION;


	if ( ( rc = ndp_tx_ll_addr ( netdev, NULL, &sin6_dest, &rsol,
				     sizeof ( rsol ), NDP_OPT_LL_SOURCE ) ) !=0)
		return rc;

	return 0;
}
