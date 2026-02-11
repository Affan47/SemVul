tls_generate_csr (TlsCreationData * creation_data,
			  gnutls_x509_privkey_t *key,
			  gchar ** csr)
{
	gnutls_x509_crq_t crq;
	size_t csr_len = 0;

	if (gnutls_x509_crq_init (&crq) < 0) {
		return g_strdup_printf(_("Error when initializing csr structure"));
	}

	if (gnutls_x509_crq_set_version (crq, 1) < 0){
		return g_strdup_printf(_("Error when setting csr version"));
	}

	gnutls_x509_crq_set_key (crq, (* key));

	if (creation_data->country) {
		gnutls_x509_crq_set_dn_by_oid (crq, GNUTLS_OID_X520_COUNTRY_NAME,
					       0, creation_data->country, strlen(creation_data->country));
	}

	if (creation_data->state) {
		gnutls_x509_crq_set_dn_by_oid (crq, GNUTLS_OID_X520_STATE_OR_PROVINCE_NAME,
					       0, creation_data->state, strlen(creation_data->state));
	}
	if (creation_data->city) {
		gnutls_x509_crq_set_dn_by_oid (crq, GNUTLS_OID_X520_LOCALITY_NAME,
					       0, creation_data->city, strlen(creation_data->city));
	}
	if (creation_data->org) {
		gnutls_x509_crq_set_dn_by_oid (crq, GNUTLS_OID_X520_ORGANIZATION_NAME,
					       0, creation_data->org, strlen(creation_data->org));
	}
	if (creation_data->ou) {
		gnutls_x509_crq_set_dn_by_oid (crq, GNUTLS_OID_X520_ORGANIZATIONAL_UNIT_NAME,
					       0, creation_data->ou, strlen(creation_data->ou));
	}
	if (creation_data->cn) {
		gnutls_x509_crq_set_dn_by_oid (crq, GNUTLS_OID_X520_COMMON_NAME,
					       0, creation_data->cn, strlen(creation_data->cn));
	}


	if (gnutls_x509_crq_sign(crq, (* key))) {
		return g_strdup_printf(_("Error when signing self-signed csr"));
	}


	(* csr) = g_new0 (gchar, 1);
	gnutls_x509_crq_export (crq, GNUTLS_X509_FMT_PEM, (* csr), &csr_len);
	g_free (* csr);


	(* csr) = g_new0 (gchar, csr_len);
	if (gnutls_x509_crq_export (crq, GNUTLS_X509_FMT_PEM, (* csr), &csr_len) < 0) {
		return g_strdup_printf(_("Error exporting CSR to PEM structure."));
	}

	gnutls_x509_crq_deinit (crq);

	return NULL;

}
