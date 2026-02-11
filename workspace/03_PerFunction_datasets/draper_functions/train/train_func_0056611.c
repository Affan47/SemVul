ssl_certificate_destroy(SSLCertificate *cert)
{
	if (cert == NULL)
		return;

	if (cert->x509_cert)
		X509_free(cert->x509_cert);
	if (cert->host)
		g_free(cert->host);
	g_free(cert);
	cert = NULL;
}
