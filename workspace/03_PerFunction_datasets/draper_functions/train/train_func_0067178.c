fctx_addopt(dns_message_t *message, unsigned int version,
	    isc_uint16_t udpsize, dns_ednsopt_t *ednsopts, size_t count)
{
	dns_rdataset_t *rdataset = NULL;
	isc_result_t result;

	result = dns_message_buildopt(message, &rdataset, version, udpsize,
				      DNS_MESSAGEEXTFLAG_DO, ednsopts, count);
	if (result != ISC_R_SUCCESS)
		return (result);
	return (dns_message_setopt(message, rdataset));
}
