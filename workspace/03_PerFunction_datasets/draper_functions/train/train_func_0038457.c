__certificate_details_populate(const char *certificate_pem)
{
	gint result;
	gnutls_datum_t pem_datum;
	gnutls_x509_crt_t certificate;
	GtkTreeStore *store = NULL;
	GObject *view = NULL;
	GtkCellRenderer *renderer = NULL;

	pem_datum.data = (guchar *) certificate_pem;
	pem_datum.size = strlen(certificate_pem);
	result = gnutls_x509_crt_init(&certificate);

	if (result < 0)
	{
		fprintf(stderr, "Error: (%s,%d): %s\n", __FILE__, __LINE__, gnutls_strerror(result));
		return;
	}

	gnutls_x509_crt_import(certificate, &pem_datum, GNUTLS_X509_FMT_PEM);
	if (result < 0)
	{
		fprintf(stderr, "Error: (%s,%d): %s\n", __FILE__, __LINE__, gnutls_strerror(result));
		return;
	}

	store = gtk_tree_store_new(CERTIFICATE_PROPERTIES_N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING);
	__certificate_properties_fill_certificate(store, &certificate);
	gnutls_x509_crt_deinit(certificate);

	view = gtk_builder_get_object(certificate_properties_window_gtkb, "certTreeView");
	renderer = gtk_cell_renderer_text_new();

	g_object_set(renderer, "yalign", 0.0, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view), -1, _("Name"), renderer, "text", CERTIFICATE_PROPERTIES_COL_NAME, NULL);
	renderer = gtk_cell_renderer_text_new();

	g_object_set(renderer, "family", "Monospace", "family-set", 1, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view), -1, _("Value"), renderer, "text", CERTIFICATE_PROPERTIES_COL_VALUE, NULL);
	gtk_tree_view_set_model(GTK_TREE_VIEW(view), GTK_TREE_MODEL(store));

	g_object_unref(store);
}
