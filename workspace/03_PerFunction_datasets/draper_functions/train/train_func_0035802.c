ldns_pkt_safe_push_rr(ldns_pkt *pkt, ldns_pkt_section sec, ldns_rr *rr)
{


	if (ldns_pkt_rr(pkt, sec, rr)) {

		return false;
	}
	return ldns_pkt_push_rr(pkt, sec, rr);
}
