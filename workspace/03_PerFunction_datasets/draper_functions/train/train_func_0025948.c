ssl_certificate_get_subject_cn(SSLCertificate *cert)
{
	gchar subject_cn[BUFFSIZE];
	size_t n = BUFFSIZE;

	if(gnutls_x509_crt_get_dn_by_oid(cert->x509_cert,
		GNUTLS_OID_X520_COMMON_NAME, 0, 0, subject_cn, &n))
		strncpy(subject_cn, _("<not in certificate>"), BUFFSIZE);

	return g_strdup(subject_cn);
}
