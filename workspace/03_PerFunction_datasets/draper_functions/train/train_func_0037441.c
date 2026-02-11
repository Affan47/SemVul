camel_certdb_get_host (CamelCertDB *certdb,
                       const gchar *hostname,
                       const gchar *fingerprint)
{
	CamelCert *cert;
	CamelCertDBKey *key;

	g_return_val_if_fail (CAMEL_IS_CERTDB (certdb), NULL);

	camel_certdb_lock (certdb, CAMEL_CERTDB_DB_LOCK);

	key = certdb_key_new (hostname, fingerprint);

	cert = g_hash_table_lookup (certdb->cert_hash, key);
	if (cert)
		camel_certdb_cert_ref (certdb, cert);

	certdb_key_free (key);

	camel_certdb_unlock (certdb, CAMEL_CERTDB_DB_LOCK);

	return cert;
}
