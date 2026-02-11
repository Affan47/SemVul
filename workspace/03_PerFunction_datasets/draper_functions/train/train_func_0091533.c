tokenlsb64_to_ipv6addrstruct(const char *addrstring, char *resultstring, ipv6calc_ipv6addr *ipv6addrp) {
	int retval = 1, result;
	int temp[4];
	char tempstring[NI_MAXHOST];

	resultstring[0] = '\0';

	if ( (ipv6calc_debug & DEBUG_libipv6addr) != 0 ) {
		fprintf(stderr, "%s: got input '%s'\n", DEBUG_function_name, addrstring);
	};

	if ( strlen(addrstring) != 16 ) {
		snprintf(resultstring, NI_MAXHOST - 1, "Error in given token '%s' is not valid (length != 16)!", addrstring);
		retval = 1;
		return (retval);
	};


	result = sscanf(addrstring, "%04x%04x%04x%04x", &temp[0], &temp[1], &temp[2], &temp[3]);
	if ( result != 4 ) {
		snprintf(resultstring, NI_MAXHOST - 1, "Error splitting address '%s', got %d items instead of 4!", addrstring, result);
		retval = 1;
		return (retval);
	};


	snprintf(tempstring, sizeof(tempstring) - 1,  "0:0:0:0:%04x:%04x:%04x:%04x", \
		(unsigned int) temp[0] ,\
		(unsigned int) temp[1], \
		(unsigned int) temp[2], \
		(unsigned int) temp[3]  \
	);


	retval = addr_to_ipv6addrstruct(tempstring, resultstring, ipv6addrp);

	return (retval);
}
