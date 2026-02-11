ipv6addr_setword(ipv6calc_ipv6addr *ipv6addrp, const unsigned int numword, const unsigned int value) {
	if ( numword > 7 ) {
		fprintf(stderr, "%s: given word number '%u' is out of range!\n", DEBUG_function_name, numword);
		exit(EXIT_FAILURE);
	};

	if ( value > 0x0000ffffu ) {
		fprintf(stderr, "%s: given value '%x' is out of range!\n", DEBUG_function_name, value);
		exit(EXIT_FAILURE);
	};

	ipv6addrp->in6_addr.s6_addr[numword * 2    ] = (uint8_t) ( ( value & 0x0000ff00 ) >>  8 );
	ipv6addrp->in6_addr.s6_addr[numword * 2 + 1] = (uint8_t) ( ( value & 0x000000ff )       );

	return;
}
