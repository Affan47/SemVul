clearacl(isc_mem_t *mctx, dns_acl_t **aclp) {
	dns_acl_t *newacl = NULL;
	isc_result_t result;
	result = dns_acl_create(mctx, 0, &newacl);
	if (result != ISC_R_SUCCESS)
		return (result);
	dns_acl_detach(aclp);
	dns_acl_attach(newacl, aclp);
	dns_acl_detach(&newacl);
	return (ISC_R_SUCCESS);
}
