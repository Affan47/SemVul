rpz_ck_dnssec(ns_client_t *client, isc_result_t qresult,
	      dns_rdataset_t *rdataset, dns_rdataset_t *sigrdataset)
{
	dns_fixedname_t fixed;
	dns_name_t *found;
	dns_rdataset_t trdataset;
	dns_rdatatype_t type;
	isc_result_t result;

	if (client->view->rpzs->p.break_dnssec || !WANTDNSSEC(client))
		return (ISC_TRUE);


	if (qresult == DNS_R_DELEGATION || qresult == ISC_R_NOTFOUND)
		return (ISC_FALSE);

	if (sigrdataset == NULL)
		return (ISC_TRUE);
	if (dns_rdataset_isassociated(sigrdataset))
		return (ISC_FALSE);


	if (rdataset == NULL || !dns_rdataset_isassociated(rdataset))
		return (ISC_TRUE);


	if (rdataset->type == dns_rdatatype_nsec ||
	    rdataset->type == dns_rdatatype_nsec3 ||
	    rdataset->type == dns_rdatatype_rrsig)
		return (ISC_FALSE);


	if ((rdataset->attributes & DNS_RDATASETATTR_NEGATIVE) == 0)
		return (ISC_TRUE);
	dns_fixedname_init(&fixed);
	found = dns_fixedname_name(&fixed);
	dns_rdataset_init(&trdataset);
	for (result = dns_rdataset_first(rdataset);
	     result == ISC_R_SUCCESS;
	     result = dns_rdataset_next(rdataset)) {
		dns_ncache_current(rdataset, found, &trdataset);
		type = trdataset.type;
		dns_rdataset_disassociate(&trdataset);
		if (type == dns_rdatatype_nsec ||
		    type == dns_rdatatype_nsec3 ||
		    type == dns_rdatatype_rrsig)
			return (ISC_FALSE);
	}
	return (ISC_TRUE);
}
