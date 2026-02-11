libipv6calc_anon_set_by_name(s_ipv6calc_anon_set *ipv6calc_anon_set, const char *name) {
	int i;

	if (strlen(name) == 0) {
		fprintf(stderr, "Name of anonymization set is empty\n");
		return 1;
	};

	DEBUGPRINT_WA(DEBUG_libipv6calc, "search for anonymization set with name: %s", name);

	for (i = 0; i < sizeof(ipv6calc_anon_set_list) / sizeof(s_ipv6calc_anon_set); i++) {
		DEBUGPRINT_WA(DEBUG_libipv6calc, "compare name: %s ? %s", name, ipv6calc_anon_set_list[i].name);

		if ((strcmp(name, ipv6calc_anon_set_list[i].name) == 0) || (strcmp(name, ipv6calc_anon_set_list[i].name_short) == 0)) {
			DEBUGPRINT_WA(DEBUG_libipv6calc, "hit name: %s = %s", name, ipv6calc_anon_set_list[i].name);

			memcpy(ipv6calc_anon_set, &ipv6calc_anon_set_list[i], sizeof(s_ipv6calc_anon_set));
			return 0;
		};
	};

	return 1;
}
