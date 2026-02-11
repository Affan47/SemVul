fill_details_page (CertificateViewerPriv *priv)
{
	GSList *iter;
	GtkTreeIter root;
	GtkTreeSelection *selection;
	gboolean root_set = FALSE;
	GtkTreeStore *hierarchy_store;

	g_return_if_fail (priv != NULL);

	gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (priv->cert_hierarchy_treeview), FALSE);

	hierarchy_store = gtk_tree_store_new (2, G_TYPE_STRING, G_TYPE_POINTER);
	gtk_tree_view_set_model (
		GTK_TREE_VIEW (priv->cert_hierarchy_treeview),
		GTK_TREE_MODEL (hierarchy_store));

	gtk_tree_view_insert_column_with_attributes (
		GTK_TREE_VIEW (priv->cert_hierarchy_treeview),
		-1, "Cert", gtk_cell_renderer_text_new (),
		"text", 0, NULL);

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (priv->cert_hierarchy_treeview));
	g_signal_connect (
		selection, "changed",
		G_CALLBACK (hierarchy_selection_changed_cb), priv);

	gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (priv->cert_fields_treeview), FALSE);

	gtk_tree_view_insert_column_with_attributes (
		GTK_TREE_VIEW (priv->cert_fields_treeview),
		-1, "Field", gtk_cell_renderer_text_new (),
		"text", 0, NULL);

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (priv->cert_fields_treeview));
	g_signal_connect (
		selection, "changed",
		G_CALLBACK (fields_selection_changed_cb), priv);


	priv->monospace_tag = gtk_text_buffer_create_tag (
		gtk_text_view_get_buffer (GTK_TEXT_VIEW (priv->cert_field_value_textview)),
		"mono", "font", "Mono", NULL);


	for (iter = priv->issuers; iter; iter = g_slist_next (iter)) {
		CERTCertificate *cert = iter->data;
		gchar *str;
		GtkTreeIter new_iter;

		if (!cert)
			continue;

		str = CERT_GetCommonName (&cert->subject);

		gtk_tree_store_insert (hierarchy_store, &new_iter, root_set ? &root : NULL, -1);
		gtk_tree_store_set (
			hierarchy_store, &new_iter,
			0, str ? str : cert->subjectName,
			1, cert,
			-1);

		root = new_iter;
		root_set = TRUE;

		if (str)
			PORT_Free (str);
	}

	gtk_tree_view_expand_all (GTK_TREE_VIEW (priv->cert_hierarchy_treeview));
}
