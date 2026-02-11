ipv6_is_on_link ( struct ipv6_miniroute *miniroute,
			     struct in6_addr *address ) {
	unsigned int i;

	for ( i = 0 ; i < ( sizeof ( address->s6_addr32 ) /
			    sizeof ( address->s6_addr32[0] ) ) ; i++ ) {
		if ( (( address->s6_addr32[i] ^ miniroute->address.s6_addr32[i])
		      & miniroute->prefix_mask.s6_addr32[i] ) != 0 )
			return 0;
	}
	return 1;
}
