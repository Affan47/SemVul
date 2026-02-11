__certificate_properties_fill_cert_ext_ExtKeyUsage (GtkTreeStore *store,
									  GtkTreeIter *parent,
									  gnutls_x509_crt_t *certificate)
{
	gint i;
	const gint BUFFER_SIZE_MAX = 1024;
	gchar usage_buffer[BUFFER_SIZE_MAX];
	gchar *usage_buffer_iterator = usage_buffer;
	GtkTreeIter l;

	for (i = 0;; i++) {
		gint result;
		gchar buffer[BUFFER_SIZE_MAX];
		gsize buffer_size = BUFFER_SIZE_MAX;
                const gchar *label = NULL;
		result = gnutls_x509_crt_get_key_purpose_oid(*certificate, i, buffer, &buffer_size, 0);

		if (result == GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE) {
			break;
		}
		if (result == GNUTLS_E_SHORT_MEMORY_BUFFER) {
			fprintf(stderr, "Error: (%s,%d): %s\n", __FILE__, __LINE__, gnutls_strerror(result));
			return;
		}
		if (result < 0) {
			fprintf(stderr, "Error: (%s,%d): %s\n", __FILE__, __LINE__, gnutls_strerror(result));
			return;
		}
		label = __certificate_properties_lookup_oid_label(certificate_properties_oid_label_table, buffer);
		usage_buffer_iterator += sprintf(usage_buffer_iterator, "%s\n", label);
	}

	*(usage_buffer_iterator - 1) = 0;
	gtk_tree_store_append(store, &l, parent);
	gtk_tree_store_set(store, &l, CERTIFICATE_PROPERTIES_COL_NAME, _("Value"),
			   CERTIFICATE_PROPERTIES_COL_VALUE, usage_buffer, -1);
}
