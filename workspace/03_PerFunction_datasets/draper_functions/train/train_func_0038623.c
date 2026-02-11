ldns_key_deep_free(ldns_key *key)
{
	unsigned char* hmac;
	if (ldns_key_pubkey_owner(key)) {
		ldns_rdf_deep_free(ldns_key_pubkey_owner(key));
	}
#ifdef HAVE_SSL
	if (ldns_key_evp_key(key)) {
		EVP_PKEY_free(ldns_key_evp_key(key));
	}
#endif
	if (ldns_key_hmac_key(key)) {
		hmac = ldns_key_hmac_key(key);
		LDNS_FREE(hmac);
	}
	LDNS_FREE(key);
}
