ipv4_arp_check ( struct net_device *netdev, const void *net_addr ) {
	const struct in_addr *address = net_addr;
	struct ipv4_miniroute *miniroute;

	list_for_each_entry ( miniroute, &ipv4_miniroutes, list ) {
		if ( ( miniroute->netdev == netdev ) &&
		     ( miniroute->address.s_addr == address->s_addr ) ) {

			return 0;
		}
	}
	return -ENOENT;
}
