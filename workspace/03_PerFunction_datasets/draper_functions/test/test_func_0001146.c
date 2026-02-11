sslcertwindow_get_invalid_str(SSLCertificate *cert)
{
	gchar *subject_cn = NULL;
	gchar *str = NULL;

	if (ssl_certificate_check_subject_cn(cert))
		return g_strdup("");

	subject_cn = ssl_certificate_get_subject_cn(cert);

	str = g_strdup_printf(_("Certificate is for %s, but connection is to %s.\n"
				"You may be connecting to a rogue server.\n\n"),
				subject_cn, cert->host);
	g_free(subject_cn);

	return str;
}
