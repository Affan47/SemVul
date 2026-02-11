process_deletetkey(dns_name_t *signer, dns_name_t *name,
		   dns_rdata_tkey_t *tkeyin, dns_rdata_tkey_t *tkeyout,
		   dns_tsig_keyring_t *ring)
{
	isc_result_t result;
	dns_tsigkey_t *tsigkey = NULL;
	dns_name_t *identity;

	result = dns_tsigkey_find(&tsigkey, name, &tkeyin->algorithm, ring);
	if (result != ISC_R_SUCCESS) {
		tkeyout->error = dns_tsigerror_badname;
		return (ISC_R_SUCCESS);
	}


	identity = dns_tsigkey_identity(tsigkey);
	if (identity == NULL || !dns_name_equal(identity, signer)) {
		dns_tsigkey_detach(&tsigkey);
		return (DNS_R_REFUSED);
	}


	dns_tsigkey_setdeleted(tsigkey);


	dns_tsigkey_detach(&tsigkey);

	return (ISC_R_SUCCESS);
}
