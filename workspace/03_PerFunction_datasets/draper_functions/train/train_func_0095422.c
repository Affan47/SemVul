arp_find_entry ( struct ll_protocol *ll_protocol,
		 struct net_protocol *net_protocol,
		 const void *net_addr ) {
	struct arp_entry *arp;

	for ( arp = arp_table ; arp < arp_table_end ; arp++ ) {
		if ( ( arp->ll_protocol == ll_protocol ) &&
		     ( arp->net_protocol == net_protocol ) &&
		     ( memcmp ( arp->net_addr, net_addr,
				net_protocol->net_addr_len ) == 0 ) )
			return arp;
	}
	return NULL;
}
