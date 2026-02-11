identifier_to_ipv6addrstruct(const char *addrstring, char *resultstring, ipv6calc_ipv6addr *ipv6addrp) {
	int retval = 1, i, ccolons = 0;
	char tempstring[NI_MAXHOST];

	resultstring[0] = '\0';

	if ( (ipv6calc_debug & DEBUG_libipv6addr) != 0 ) {
		fprintf(stderr, "%s: Got input '%s'\n", DEBUG_function_name, addrstring);
	};

	if ((strlen(addrstring) < 2) || (strlen(addrstring) > 19)) {


		snprintf(resultstring, NI_MAXHOST - 1, "Error in given identifier identifier, has not 2 to 19 chars!");
		retval = 1;
		return (retval);
	};


	for (i = 0; i < (int) strlen(addrstring); i++) {
		if (addrstring[i] == ':') {
			ccolons++;
		};
	};
	if ((ccolons < 2) || (ccolons > 3)) {
		snprintf(resultstring, NI_MAXHOST - 1, "Error in given identifier '%s' is not valid!", addrstring);
		retval = 1;
		return (retval);
	};


	snprintf(tempstring, sizeof(tempstring) - 1, "0:0:0:0:%s", addrstring);


	retval = addr_to_ipv6addrstruct(tempstring, resultstring, ipv6addrp);

	if ( (ipv6calc_debug & DEBUG_libipv6addr) != 0 ) {
		fprintf(stderr, "%s: result string '%s'\n", DEBUG_function_name, resultstring);
	};

	return (retval);
}
