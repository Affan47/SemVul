find_match(struct entry* entries, ldns_pkt* query_pkt,
	enum transport_type transport)
{
	struct entry* p = entries;
	ldns_pkt* reply = NULL;
	for(p=entries; p; p=p->next) {
		verbose(3, "comparepkt: ");
		reply = p->reply_list->reply;
		if(p->match_opcode && ldns_pkt_get_opcode(query_pkt) !=
			ldns_pkt_get_opcode(reply)) {
			verbose(3, "bad opcode\n");
			continue;
		}
		if(p->match_qtype && get_qtype(query_pkt) != get_qtype(reply)) {
			verbose(3, "bad qtype\n");
			continue;
		}
		if(p->match_qname) {
			if(!get_owner(query_pkt) || !get_owner(reply) ||
				ldns_dname_compare(
				get_owner(query_pkt), get_owner(reply)) != 0) {
				verbose(3, "bad qname\n");
				continue;
			}
		}
		if(p->match_subdomain) {
			if(!get_owner(query_pkt) || !get_owner(reply) ||
				(ldns_dname_compare(get_owner(query_pkt),
				get_owner(reply)) != 0 &&
				!ldns_dname_is_subdomain(
				get_owner(query_pkt), get_owner(reply))))
			{
				verbose(3, "bad subdomain\n");
				continue;
			}
		}
		if(p->match_serial && get_serial(query_pkt) != p->ixfr_soa_serial) {
				verbose(3, "bad serial\n");
				continue;
		}
		if(p->match_do && !ldns_pkt_edns_do(query_pkt)) {
			verbose(3, "no DO bit set\n");
			continue;
		}
		if(p->match_noedns && ldns_pkt_edns(query_pkt)) {
			verbose(3, "bad; EDNS OPT present\n");
			continue;
		}
		if(p->match_ednsdata_raw &&
				!match_ednsdata(query_pkt, p->reply_list)) {
			verbose(3, "bad EDNS data match.\n");
			continue;
		}
		if(p->match_transport != transport_any && p->match_transport != transport) {
			verbose(3, "bad transport\n");
			continue;
		}
		if(p->match_all && !match_all(query_pkt, reply, p->match_ttl)) {
			verbose(3, "bad allmatch\n");
			continue;
		}
		verbose(3, "match!\n");
		return p;
	}
	return NULL;
}
