__certificate_properties_fill_cert_subject (GtkTreeStore *store, GtkTreeIter *parent, gnutls_x509_crt_t *certificate)
{
	int result;
	size_t buffer_size = 0;
	gchar *buffer = NULL;
	gchar *value = NULL;
	GtkTreeIter j;

	result = gnutls_x509_crt_get_dn(*certificate, 0, &buffer_size);
	if (result != GNUTLS_E_SHORT_MEMORY_BUFFER) {
		fprintf(stderr, "Error: (%s,%d): %s\n", __FILE__, __LINE__, gnutls_strerror(result));
		return;
	}
	buffer = g_new0 (gchar, buffer_size);
	if (!buffer) {
		fprintf(stderr, "Error: (%s,%d): %s\n", __FILE__, __LINE__, "Not enough memory!");
		return;
	}

	result = gnutls_x509_crt_get_dn(*certificate, buffer, &buffer_size);
	if (result < 0) {
		fprintf(stderr, "Error: (%s,%d): %s\n", __FILE__, __LINE__, gnutls_strerror(result));
		return;
	}
	value = __certificate_properties_dump_RDNSequence(buffer, buffer_size);

	g_free(buffer);

	gtk_tree_store_append(store, &j, parent);
	gtk_tree_store_set(store, &j, CERTIFICATE_PROPERTIES_COL_NAME, _("Subject"), CERTIFICATE_PROPERTIES_COL_VALUE, value, -1);

	g_free(value);
}
