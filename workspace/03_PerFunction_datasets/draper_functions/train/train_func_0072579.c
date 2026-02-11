notify_treeview_new (GtkWidget *box)
{
	GtkListStore *store;
	GtkWidget *view;
	GtkTreeViewColumn *col;
	int col_id;

	store = gtk_list_store_new (N_COLUMNS,
	                            G_TYPE_STRING,
	                            G_TYPE_STRING,
	                            G_TYPE_STRING,
	                            G_TYPE_STRING,
	                            G_TYPE_POINTER,
										 G_TYPE_POINTER
	                           );
	g_return_val_if_fail (store != NULL, NULL);

	view = gtkutil_treeview_new (box, GTK_TREE_MODEL (store),
	                             notify_treecell_property_mapper,
	                             USER_COLUMN, _("Name"),
	                             STATUS_COLUMN, _("Status"),
	                             SERVER_COLUMN, _("Network"),
	                             SEEN_COLUMN, _("Last Seen"), -1);
	gtk_tree_view_column_set_expand (gtk_tree_view_get_column (GTK_TREE_VIEW (view), 0), TRUE);

	for (col_id=0; (col = gtk_tree_view_get_column (GTK_TREE_VIEW (view), col_id));
	     col_id++)
			gtk_tree_view_column_set_alignment (col, 0.5);

	g_signal_connect (G_OBJECT (gtk_tree_view_get_selection (GTK_TREE_VIEW (view))),
							"changed", G_CALLBACK (notify_row_cb), view);

	gtk_widget_show (view);
	return view;
}
