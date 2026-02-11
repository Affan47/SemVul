ldns_dnssec_data_chain_deep_free(ldns_dnssec_data_chain *chain)
{
	ldns_rr_list_deep_free(chain->rrset);
	ldns_rr_list_deep_free(chain->signatures);
	if (chain->parent) {
		ldns_dnssec_data_chain_deep_free(chain->parent);
	}
	LDNS_FREE(chain);
}
