certdb_cert_free (CamelCertDB *certdb,
                  CamelCert *cert)
{
	g_free (cert->issuer);
	g_free (cert->subject);
	g_free (cert->hostname);
	g_free (cert->fingerprint);
	if (cert->rawcert)
		g_byte_array_free (cert->rawcert, TRUE);
}
