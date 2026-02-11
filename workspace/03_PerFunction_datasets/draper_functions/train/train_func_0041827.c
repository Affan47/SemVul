gpk_log_refilter (void)
{
	guint i;
	gboolean ret;
	PkTransactionPast *item;
	GtkWidget *widget;
	const gchar *package;
	GtkTreeView *treeview;
	GtkTreeModel *model;


	g_free (filter);
	widget = GTK_WIDGET (gtk_builder_get_object (builder, "entry_package"));
	package = gtk_entry_get_text (GTK_ENTRY(widget));
	if (package != NULL && package[0] != '\0')
		filter = g_strdup (package);
	else
		filter = NULL;

	g_debug ("len=%i", transactions->len);


	treeview = GTK_TREE_VIEW (gtk_builder_get_object (builder, "treeview_simple"));
	model = gtk_tree_view_get_model (treeview);
	gpk_log_mark_nonactive (model);


	for (i=0; i<transactions->len; i++) {
		item = g_ptr_array_index (transactions, i);
		ret = gpk_log_filter (item);
		if (ret)
			gpk_log_add_item (item);
	}


	gpk_log_remove_nonactive (model);
}
