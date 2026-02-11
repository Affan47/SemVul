ldns_dnssec_build_data_chain_other(ldns_resolver *res,
					    uint16_t qflags,
						ldns_dnssec_data_chain *new_chain,
						ldns_rdf *key_name,
						ldns_rr_class c,
						ldns_rr_list *dss)
{


	ldns_pkt *my_pkt;
	ldns_rr_list *signatures2;

	new_chain->parent_type = 1;

	my_pkt = ldns_resolver_query(res,
							key_name,
							LDNS_RR_TYPE_DS,
							c,
							qflags);
	if (my_pkt) {
	dss = ldns_pkt_rr_list_by_name_and_type(my_pkt,
									key_name,
									LDNS_RR_TYPE_DS,
									LDNS_SECTION_ANY_NOQUESTION
									);
	if (dss) {
		new_chain->parent = ldns_dnssec_build_data_chain(res,
												qflags,
												dss,
												my_pkt,
												NULL);
		new_chain->parent->packet_qtype = LDNS_RR_TYPE_DS;
		ldns_rr_list_deep_free(dss);
	}
	ldns_pkt_free(my_pkt);
	}

	my_pkt = ldns_resolver_query(res,
							key_name,
							LDNS_RR_TYPE_DNSKEY,
							c,
							qflags);
	if (my_pkt) {
	signatures2 = ldns_pkt_rr_list_by_name_and_type(my_pkt,
										   key_name,
										   LDNS_RR_TYPE_RRSIG,
										   LDNS_SECTION_ANSWER);
	if (signatures2) {
		if (new_chain->signatures) {
			printf("There were already sigs!\n");
			ldns_rr_list_deep_free(new_chain->signatures);
			printf("replacing the old sigs\n");
		}
		new_chain->signatures = signatures2;
	}
	ldns_pkt_free(my_pkt);
	}
}
