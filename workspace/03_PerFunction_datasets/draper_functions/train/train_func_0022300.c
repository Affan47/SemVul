check_node(dns_rdataset_t *rootns, dns_name_t *name,
	   dns_rdatasetiter_t *rdsiter) {
	isc_result_t result;
	dns_rdataset_t rdataset;

	dns_rdataset_init(&rdataset);
	result = dns_rdatasetiter_first(rdsiter);
	while (result == ISC_R_SUCCESS) {
		dns_rdatasetiter_current(rdsiter, &rdataset);
		switch (rdataset.type) {
		case dns_rdatatype_a:
		case dns_rdatatype_aaaa:
			result = in_rootns(rootns, name);
			if (result != ISC_R_SUCCESS)
				goto cleanup;
			break;
		case dns_rdatatype_ns:
			if (dns_name_compare(name, dns_rootname) == 0)
				break;

		default:
			result = ISC_R_FAILURE;
			goto cleanup;
		}
		dns_rdataset_disassociate(&rdataset);
		result = dns_rdatasetiter_next(rdsiter);
	}
	if (result == ISC_R_NOMORE)
		result = ISC_R_SUCCESS;
 cleanup:
	if (dns_rdataset_isassociated(&rdataset))
		dns_rdataset_disassociate(&rdataset);
	return (result);
}
