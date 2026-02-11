camel_certdb_nss_cert_set (CamelCertDB *certdb,
                           CamelCert *ccert,
                           CERTCertificate *cert)
{
	gchar *filename, *fingerprint;
	CamelStream *stream;
	const gchar *cert_dir;

	fingerprint = ccert->fingerprint;

	if (ccert->rawcert == NULL)
		ccert->rawcert = g_byte_array_new ();

	g_byte_array_set_size (ccert->rawcert, cert->derCert.len);
	memcpy (ccert->rawcert->data, cert->derCert.data, cert->derCert.len);

	cert_dir = tcp_stream_ssl_get_cert_dir ();
	filename = g_build_filename (cert_dir, fingerprint, NULL);

	stream = camel_stream_fs_new_with_name (
		filename, O_WRONLY | O_CREAT | O_TRUNC, 0600, NULL);
	if (stream != NULL) {
		if (camel_stream_write (
			stream, (const gchar *) ccert->rawcert->data,
			ccert->rawcert->len, NULL, NULL) == -1) {
			g_warning (
				"Could not save cert: %s: %s",
				filename, g_strerror (errno));
			g_unlink (filename);
		}
		camel_stream_close (stream, NULL, NULL);
		g_object_unref (stream);
	} else {
		g_warning (
			"Could not save cert: %s: %s",
			filename, g_strerror (errno));
	}

	g_free (filename);
}
