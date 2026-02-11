ldns_resolver_prepare_query_pkt(ldns_pkt **query_pkt, ldns_resolver *r,
                                const ldns_rdf *name, ldns_rr_type t,
                                ldns_rr_class c, uint16_t flags)
{
	struct timeval now;


	if (t == LDNS_RR_TYPE_IXFR) {
		*query_pkt = ldns_pkt_ixfr_request_new(ldns_rdf_clone(name),
			c, flags, NULL);
	} else {
		*query_pkt = ldns_pkt_query_new(ldns_rdf_clone(name), t, c, flags);
	}
	if (!*query_pkt) {
		return LDNS_STATUS_ERR;
	}


	if (ldns_resolver_dnssec(r)) {
		if (ldns_resolver_edns_udp_size(r) == 0) {
			ldns_resolver_set_edns_udp_size(r, 4096);
		}
		ldns_pkt_set_edns_do(*query_pkt, true);
		if (ldns_resolver_dnssec_cd(r) || (flags & LDNS_CD)) {
			ldns_pkt_set_cd(*query_pkt, true);
		}
	}


	if (ldns_resolver_edns_udp_size(r) != 0) {
		ldns_pkt_set_edns_udp_size(*query_pkt, ldns_resolver_edns_udp_size(r));
	}


	now.tv_sec = time(NULL);
	now.tv_usec = 0;
	ldns_pkt_set_timestamp(*query_pkt, now);


	if (ldns_resolver_debug(r)) {
		ldns_pkt_print(stdout, *query_pkt);
	}


	if (ldns_pkt_id(*query_pkt) == 0) {
		ldns_pkt_set_random_id(*query_pkt);
	}

	return LDNS_STATUS_OK;
}
