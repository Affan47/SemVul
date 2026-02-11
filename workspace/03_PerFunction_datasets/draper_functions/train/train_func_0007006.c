ldns_dane_match_any_cert_with_data(STACK_OF(X509)* chain,
		ldns_tlsa_selector      selector,
		ldns_tlsa_matching_type matching_type,
		ldns_rdf* data, bool ca)
{
	ldns_status s = LDNS_STATUS_DANE_TLSA_DID_NOT_MATCH;
	size_t n, i;
	X509* cert;

	n = (size_t)sk_X509_num(chain);
	for (i = 0; i < n; i++) {
		cert = sk_X509_pop(chain);
		if (! cert) {
			s = LDNS_STATUS_SSL_ERR;
			break;
		}
		s = ldns_dane_match_cert_with_data(cert,
				selector, matching_type, data);
		if (ca && s == LDNS_STATUS_OK && ! X509_check_ca(cert)) {
			s = LDNS_STATUS_DANE_NON_CA_CERTIFICATE;
		}
		X509_free(cert);
		if (s != LDNS_STATUS_DANE_TLSA_DID_NOT_MATCH) {
			break;
		}


	}
	return s;
}
