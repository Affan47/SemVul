ipv6addrstruct_maskprefix(ipv6calc_ipv6addr *ipv6addrp) {
	unsigned int nbit, nword;
	uint16_t mask, newword;
	int i;

	if ( (ipv6calc_debug & DEBUG_libipv6addr) != 0 ) {
		fprintf(stderr, "%s: called\n", DEBUG_function_name);
	};

	if (ipv6addrp->flag_prefixuse != 1) {

		return;
	};

	for (i = 127; i >= 0; i--) {
		nbit = (unsigned int) i;
		if (nbit >= (unsigned int) ipv6addrp->prefixlength) {


			nword = (nbit & 0x70) >> 4;


			mask = ((uint16_t) 0x8000u) >> (( ((uint16_t) nbit) & ((uint16_t) 0x0fu)));
			newword = ipv6addr_getword(ipv6addrp, nword) & (~ mask );

			if ( (ipv6calc_debug & DEBUG_libipv6addr) != 0 ) {
				fprintf(stderr, "%s: bit: %u = nword: %u, mask: %04x, word: %04x newword: %04x\n", DEBUG_function_name, nbit, nword, (unsigned int) mask, (unsigned int) ipv6addr_getword(ipv6addrp, nword), (unsigned int) newword);
			};

			ipv6addr_setword(ipv6addrp, nword, (unsigned int) newword);
		};
	};
}
