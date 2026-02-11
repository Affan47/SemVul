libipv6calc_anon_supported(const s_ipv6calc_anon_set *ipv6calc_anon_set) {

	if (ipv6calc_anon_set->method == ANON_METHOD_KEEPTYPEASNCC) {

		if (libipv6calc_db_wrapper_has_features(ANON_METHOD_KEEPTYPEASNCC_IPV4_REQ_DB | ANON_METHOD_KEEPTYPEASNCC_IPV6_REQ_DB) == 1) {
			return(2);
		} else {
			if (libipv6calc_db_wrapper_has_features(IPV6CALC_DB_IPV4_TO_CC) != 1) {
				fprintf(stderr, "ipv6calc anonymization method not supported, missing included/available database: IPv4->CountryCode (GeoIP)\n");
			};
			if (libipv6calc_db_wrapper_has_features(IPV6CALC_DB_IPV6_TO_CC) != 1) {
				fprintf(stderr, "ipv6calc anonymization method not supported, missing included/available database: IPv6->CountryCode (GeoIP)\n");
			};
			if (libipv6calc_db_wrapper_has_features(IPV6CALC_DB_IPV4_TO_AS) != 1) {
				fprintf(stderr, "ipv6calc anonymization method not supported, missing included/available database: IPv4->AutonomousSystemNumber (GeoIP)\n");
			};
			if (libipv6calc_db_wrapper_has_features(IPV6CALC_DB_IPV6_TO_AS) != 1) {
				fprintf(stderr, "ipv6calc anonymization method not supported, missing included/available database: IPv6->AutonomousSystemNumber (GeoIP)\n");
			};
			return(0);
		};
	} else {
		return(1);
	};
}
