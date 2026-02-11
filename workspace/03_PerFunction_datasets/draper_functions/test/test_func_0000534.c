uri_opener_double_clicked(GtkTreeView		*list_view,
				   	GtkTreePath		*path,
				   	GtkTreeViewColumn	*column,
				   	gpointer		 data)
{
	ClickableText *uri;
	GtkTreeIter iter;
	GtkTreeModel *model = gtk_tree_view_get_model(list_view);

	if (!gtk_tree_model_get_iter(model, &iter, path))
		return;

	gtk_tree_model_get(model, &iter,
			   URI_OPENER_DATA, &uri,
			   -1);

	if (!uri)
		return;

	if (textview_uri_security_check(opener.msgview->mimeview->textview, uri) == TRUE)
		open_uri(uri->uri,
			 prefs_common_get_uri_cmd());
}
