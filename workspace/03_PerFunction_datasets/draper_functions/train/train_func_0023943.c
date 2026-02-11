add_ipv6_address ( struct net_device *netdev, struct in6_addr prefix,
		       int prefix_len, struct in6_addr address,
		       struct in6_addr gateway ) {
	struct ipv6_miniroute *miniroute;


	del_ipv6_address ( netdev );


	miniroute = add_ipv6_miniroute ( netdev, prefix, prefix_len, address,
					 gateway );
	if ( ! miniroute )
		return -ENOMEM;

	return 0;
}
