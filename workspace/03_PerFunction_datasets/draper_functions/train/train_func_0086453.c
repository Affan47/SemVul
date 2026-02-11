dns_acl_create(isc_mem_t *mctx, int n, dns_acl_t **target) {
	isc_result_t result;
	dns_acl_t *acl;


	if (n == 0)
		n = 1;

	acl = isc_mem_get(mctx, sizeof(*acl));
	if (acl == NULL)
		return (ISC_R_NOMEMORY);
	acl->mctx = mctx;
	acl->name = NULL;

	result = isc_refcount_init(&acl->refcount, 1);
	if (result != ISC_R_SUCCESS) {
		isc_mem_put(mctx, acl, sizeof(*acl));
		return (result);
	}

	result = dns_iptable_create(mctx, &acl->iptable);
	if (result != ISC_R_SUCCESS) {
		isc_mem_put(mctx, acl, sizeof(*acl));
		return (result);
	}

	acl->elements = NULL;
	acl->alloc = 0;
	acl->length = 0;
	acl->has_negatives = ISC_FALSE;

	ISC_LINK_INIT(acl, nextincache);


	acl->magic = DNS_ACL_MAGIC;

	acl->elements = isc_mem_get(mctx, n * sizeof(dns_aclelement_t));
	if (acl->elements == NULL) {
		result = ISC_R_NOMEMORY;
		goto cleanup;
	}
	acl->alloc = n;
	memset(acl->elements, 0, n * sizeof(dns_aclelement_t));
	*target = acl;
	return (ISC_R_SUCCESS);

 cleanup:
	dns_acl_detach(&acl);
	return (result);
}
