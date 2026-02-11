ibft_set_ipaddr ( struct ibft_ipaddr *ipaddr, struct in_addr in ) {
	memset ( ipaddr, 0, sizeof ( *ipaddr ) );
	if ( in.s_addr ) {
		ipaddr->in = in;
		ipaddr->ones = 0xffff;
	}
}
