mark_lease_unavailable(struct ipv6_pool *pool, const struct in6_addr *addr) {
	struct iasubopt *dummy_iasubopt;
	isc_result_t result;

	dummy_iasubopt = NULL;
	result = iasubopt_allocate(&dummy_iasubopt, MDL);
	if (result == ISC_R_SUCCESS) {
		dummy_iasubopt->addr = *addr;
		iasubopt_hash_add(pool->leases, &dummy_iasubopt->addr,
				  sizeof(*addr), dummy_iasubopt, MDL);
	}
	return result;
}
