ssl_certificate_save(SSLCertificate *cert)
{
	char *file, *port;
	FILE *fp;

	file = g_strconcat(config_dir, G_DIR_SEPARATOR_S,
		"certs", G_DIR_SEPARATOR_S, NULL);

	if (!is_dir_exist(file))
		mkdir(file, S_IRWXU);

	g_free(file);

	port = g_strdup_printf("%d", cert->port);
	file = g_strconcat(config_dir, G_DIR_SEPARATOR_S,
		"certs", G_DIR_SEPARATOR_S,
		cert->host, ".", port, ".cert", NULL);

	g_free(port);
	fp = fopen(file, "wb");
	if (fp == NULL) {
		g_free(file);
		eb_debug(DBG_CORE, "Can't save certificate !\n");
		return;
	}
	i2d_X509_fp(fp, cert->x509_cert);
	g_free(file);
	fclose(fp);

}
