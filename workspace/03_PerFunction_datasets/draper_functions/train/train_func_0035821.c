ipv6addr_getregistry(const ipv6calc_ipv6addr *ipv6addrp) {
	char resultstring[NI_MAXHOST];
	int i;

	i = libipv6addr_get_registry_string(ipv6addrp, resultstring);

	if (i == 2) {
		return(IPV6_ADDR_REGISTRY_RESERVED);
	} else if (i != 0) {
		return(IPV6_ADDR_REGISTRY_UNKNOWN);
	};

#ifdef SUPPORT_DB_IPV6
	if (strcmp(resultstring, "IANA") == 0) {
		return(IPV6_ADDR_REGISTRY_IANA);
	} else if (strcmp(resultstring, "APNIC") == 0) {
		return(IPV6_ADDR_REGISTRY_APNIC);
	} else if (strcmp(resultstring, "ARIN") == 0) {
		return(IPV6_ADDR_REGISTRY_ARIN);
	} else if (strcmp(resultstring, "RIPENCC") == 0) {
		return(IPV6_ADDR_REGISTRY_RIPE);
	} else if (strcmp(resultstring, "LACNIC") == 0) {
		return(IPV6_ADDR_REGISTRY_LACNIC);
	} else if (strcmp(resultstring, "AFRINIC") == 0) {
		return(IPV6_ADDR_REGISTRY_AFRINIC);
	} else if (strcmp(resultstring, "6BONE") == 0) {
		return(IPV6_ADDR_REGISTRY_6BONE);
	} else if (strcmp(resultstring, "6TO4") == 0) {
		return(IPV6_ADDR_REGISTRY_RESERVED);
	} else {
		return(IPV6_ADDR_REGISTRY_UNKNOWN);
	};
#else
	return(IPV6_ADDR_REGISTRY_UNKNOWN);
#endif
}
