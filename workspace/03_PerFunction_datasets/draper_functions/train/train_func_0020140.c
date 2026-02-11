ipv4addr_filter_parse(s_ipv6calc_filter_ipv4addr *filter, const char *token) {
	int i, result = 1, negate = 0, offset = 0;
	const char *prefix = "ipv4";
	const char *prefixdot = "ipv4.";

	if (token == NULL) {
		return (result);
	};

	DEBUGPRINT_WA(DEBUG_libipv4addr, "input: %s", token);

	if (token[0] == '^') {
		DEBUGPRINT_WA(DEBUG_libipv4addr, "found negate prefix in token: %s", token);

		negate = 1;
		offset += 1;
	};

	if (strcmp(token + offset, prefix) == 0) {

		if (negate == 1) {
			filter->typeinfo_may_not_have = ~IPV4_ADDR_ANY;
		} else {
			filter->typeinfo_must_have = IPV4_ADDR_ANY;
		};
		filter->active = 1;
		result = 0;
		goto END_ipv4addr_filter_parse;

	} else if (strncmp(token + offset, prefixdot, strlen(prefixdot)) == 0) {

		offset += strlen(prefixdot);
		result = 2;

	} else if (strstr(token, ".") != NULL) {

		DEBUGPRINT_WA(DEBUG_libipv4addr, "prefix did not match: %s", token + offset);
		return(1);
	};

	for (i = 0; i < (int) (sizeof(ipv6calc_ipv4addrtypestrings) / sizeof(ipv6calc_ipv4addrtypestrings[0])); i++ ) {
		DEBUGPRINT_WA(DEBUG_libipv4addr, "check token against: %s", ipv6calc_ipv4addrtypestrings[i].token);

		if (strcmp(ipv6calc_ipv4addrtypestrings[i].token, token + offset) == 0) {
			DEBUGPRINT_WA(DEBUG_libipv4addr, "token match: %s", ipv6calc_ipv4addrtypestrings[i].token);

			if (negate == 1) {
				filter->typeinfo_may_not_have |= ipv6calc_ipv4addrtypestrings[i].number;
			} else {
				filter->typeinfo_must_have |= ipv6calc_ipv4addrtypestrings[i].number;
			};
			filter->active = 1;
			result = 0;
			break;
		};
	};

	if (result != 0) {
		DEBUGPRINT_WA(DEBUG_libipv4addr, "token not supported: %s",token);
		return (result);
	};

END_ipv4addr_filter_parse:
	DEBUGPRINT_WA(DEBUG_libipv4addr, "filter 'must_have'   : 0x%08x", filter->typeinfo_must_have);
	DEBUGPRINT_WA(DEBUG_libipv4addr, "filter 'may_not_have': 0x%08x", filter->typeinfo_may_not_have);
	DEBUGPRINT_WA(DEBUG_libipv4addr, "filter 'active': %d", filter->active);

	return (result);
}
