on_treeview_row_expanded(GtkWidget *widget, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data)
{
	gchar *uri;

	gtk_tree_model_get(GTK_TREE_MODEL(treestore), iter, TREEBROWSER_COLUMN_URI, &uri, -1);
	if (uri == NULL)
		return;

	if (flag_on_expand_refresh == FALSE)
	{
		flag_on_expand_refresh = TRUE;
		treebrowser_browse(uri, iter);
		gtk_tree_view_expand_row(GTK_TREE_VIEW(treeview), path, FALSE);
		flag_on_expand_refresh = FALSE;
	}
	if (CONFIG_SHOW_ICONS)
	{
		GdkPixbuf *icon = utils_pixbuf_from_stock(GTK_STOCK_OPEN);

		gtk_tree_store_set(treestore, iter, TREEBROWSER_COLUMN_ICON, icon, -1);
		g_object_unref(icon);
	}

	g_free(uri);
}
