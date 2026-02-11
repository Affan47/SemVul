try_client_v6_address(struct iasubopt **addr,
		      struct ipv6_pool *pool,
		      const struct data_string *requested_addr)
{
	struct in6_addr tmp_addr;
	isc_result_t result;

	if (requested_addr->len < sizeof(tmp_addr)) {
		return DHCP_R_INVALIDARG;
	}
	memcpy(&tmp_addr, requested_addr->data, sizeof(tmp_addr));
	if (IN6_IS_ADDR_UNSPECIFIED(&tmp_addr)) {
		return ISC_R_FAILURE;
	}


	if (!ipv6_in_pool(&tmp_addr, pool)) {
		return ISC_R_ADDRNOTAVAIL;
	}

	if (lease6_exists(pool, &tmp_addr)) {
		return ISC_R_ADDRINUSE;
	}

	result = iasubopt_allocate(addr, MDL);
	if (result != ISC_R_SUCCESS) {
		return result;
	}
	(*addr)->addr = tmp_addr;
	(*addr)->plen = 0;


	result = add_lease6(pool, *addr, cur_time + 120);
	if (result != ISC_R_SUCCESS) {
		iasubopt_dereference(addr, MDL);
	}
	return result;
}
