load(dns_zone_t *zone, void *uap) {
	isc_result_t result;
	UNUSED(uap);

	result = dns_zone_load(zone);
	if (result == DNS_R_CONTINUE || result == DNS_R_UPTODATE)
		result = ISC_R_SUCCESS;

	return (result);
}
