match_ednsdata(ldns_pkt* q, struct reply_packet* p)
{
	size_t qdlen, pdlen;
	uint8_t *qd, *pd;
	if(!ldns_pkt_edns(q) || !ldns_pkt_edns_data(q)) {
		verbose(3, "No EDNS data\n");
		return 0;
	}
	qdlen = ldns_rdf_size(ldns_pkt_edns_data(q));
	pdlen = ldns_buffer_limit(p->raw_ednsdata);
	qd = ldns_rdf_data(ldns_pkt_edns_data(q));
	pd = ldns_buffer_begin(p->raw_ednsdata);
	if( qdlen == pdlen && 0 == memcmp(qd, pd, qdlen) ) return 1;
	verbose(3, "EDNS data does not match.\n");
	verbose_hex(3, qd, qdlen, "q:");
	verbose_hex(3, pd, pdlen, "p:");
	return 0;
}
