ldns_dnssec_rrsets_contains_type(ldns_dnssec_rrsets *rrsets,
                                 ldns_rr_type type)
{
	ldns_dnssec_rrsets *cur_rrset = rrsets;
	while (cur_rrset) {
		if (cur_rrset->type == type) {
			return 1;
		}
		cur_rrset = cur_rrset->next;
	}
	return 0;
}
