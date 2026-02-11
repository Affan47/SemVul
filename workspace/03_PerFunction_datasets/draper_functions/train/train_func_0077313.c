get_serial(ldns_pkt* p)
{
	ldns_rr *rr = ldns_rr_list_rr(ldns_pkt_authority(p), 0);
	ldns_rdf *rdf;
	uint32_t val;
	if(!rr) return 0;
	rdf = ldns_rr_rdf(rr, 2);
	if(!rdf) return 0;
	val = ldns_rdf2native_int32(rdf);
	verbose(3, "found serial %u in msg. ", (int)val);
	return val;
}
