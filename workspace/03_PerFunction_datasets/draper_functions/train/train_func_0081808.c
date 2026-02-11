e_preferences_window_add_page (EPreferencesWindow *window,
                               const gchar *page_name,
                               const gchar *icon_name,
                               const gchar *caption,
                               const gchar *help_target,
                               EPreferencesWindowCreatePageFn create_fn,
                               gint sort_order)
{
	GtkTreeRowReference *reference;
	GtkIconView *icon_view;
	GtkNotebook *notebook;
	GtkTreeModel *model;
	GtkTreePath *path;
	GHashTable *index;
	GdkPixbuf *pixbuf;
	GtkTreeIter iter;
	GtkWidget *align;
	gint page;

	g_return_if_fail (E_IS_PREFERENCES_WINDOW (window));
	g_return_if_fail (create_fn != NULL);
	g_return_if_fail (page_name != NULL);
	g_return_if_fail (icon_name != NULL);
	g_return_if_fail (caption != NULL);

	icon_view = GTK_ICON_VIEW (window->priv->icon_view);
	notebook = GTK_NOTEBOOK (window->priv->notebook);

	page = gtk_notebook_get_n_pages (notebook);
	model = GTK_TREE_MODEL (window->priv->store);
	pixbuf = preferences_window_load_pixbuf (icon_name);

	gtk_list_store_append (GTK_LIST_STORE (model), &iter);

	gtk_list_store_set (
		GTK_LIST_STORE (model), &iter,
		COLUMN_ID, page_name,
		COLUMN_TEXT, caption,
		COLUMN_HELP, help_target,
		COLUMN_PIXBUF, pixbuf,
		COLUMN_PAGE, page,
		COLUMN_SORT, sort_order,
		-1);

	index = window->priv->index;
	path = gtk_tree_model_get_path (model, &iter);
	reference = gtk_tree_row_reference_new (model, path);
	g_hash_table_insert (index, g_strdup (page_name), reference);
	gtk_tree_path_free (path);

	align = g_object_new (GTK_TYPE_ALIGNMENT, NULL);
	gtk_widget_show (GTK_WIDGET (align));
	g_object_set_data (G_OBJECT (align), "create_fn", create_fn);
	gtk_notebook_append_page (notebook, align, NULL);
	gtk_container_child_set (
		GTK_CONTAINER (notebook), align,
		"tab-fill", FALSE, "tab-expand", FALSE, NULL);


	gtk_icon_view_set_item_width (icon_view, -1);
	gtk_widget_queue_resize (GTK_WIDGET (window));
}
