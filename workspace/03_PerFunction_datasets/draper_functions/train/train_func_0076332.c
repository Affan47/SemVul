allowed(isc_netaddr_t *addr, dns_name_t *signer, dns_acl_t *acl) {
	int match;
	isc_result_t result;

	if (acl == NULL)
		return (ISC_TRUE);
	result = dns_acl_match(addr, signer, acl, &ns_g_server->aclenv,
			       &match, NULL);
	if (result == ISC_R_SUCCESS && match > 0)
		return (ISC_TRUE);
	return (ISC_FALSE);
}
