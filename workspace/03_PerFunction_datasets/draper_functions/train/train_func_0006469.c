ldns_rrset_use_signature_ttl(ldns_rr_list* rrset_clone, ldns_rr* rrsig)
{
	uint32_t orig_ttl;
	uint16_t i;
	uint8_t label_count;
	ldns_rdf *wildcard_name;
	ldns_rdf *wildcard_chopped;
	ldns_rdf *wildcard_chopped_tmp;

	if ((rrsig == NULL) || ldns_rr_rd_count(rrsig) < 4) {
		return;
	}

	orig_ttl = ldns_rdf2native_int32( ldns_rr_rdf(rrsig, 3));
	label_count = ldns_rdf2native_int8(ldns_rr_rdf(rrsig, 2));

	for(i = 0; i < ldns_rr_list_rr_count(rrset_clone); i++) {
		if (label_count <
		    ldns_dname_label_count(
			   ldns_rr_owner(ldns_rr_list_rr(rrset_clone, i)))) {
			(void) ldns_str2rdf_dname(&wildcard_name, "*");
			wildcard_chopped = ldns_rdf_clone(ldns_rr_owner(
				ldns_rr_list_rr(rrset_clone, i)));
			while (label_count < ldns_dname_label_count(wildcard_chopped)) {
				wildcard_chopped_tmp = ldns_dname_left_chop(
					wildcard_chopped);
				ldns_rdf_deep_free(wildcard_chopped);
				wildcard_chopped = wildcard_chopped_tmp;
			}
			(void) ldns_dname_cat(wildcard_name, wildcard_chopped);
			ldns_rdf_deep_free(wildcard_chopped);
			ldns_rdf_deep_free(ldns_rr_owner(ldns_rr_list_rr(
				rrset_clone, i)));
			ldns_rr_set_owner(ldns_rr_list_rr(rrset_clone, i),
				wildcard_name);
		}
		ldns_rr_set_ttl(ldns_rr_list_rr(rrset_clone, i), orig_ttl);

		ldns_rr2canonical(ldns_rr_list_rr(rrset_clone, i));
	}
}
