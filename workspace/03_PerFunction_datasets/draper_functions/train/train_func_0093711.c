create_tree_view(GigoloWindow *window)
{
	GigoloWindowPrivate *priv = GIGOLO_WINDOW_GET_PRIVATE(window);
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeSelection *sel;

	priv->treeview = gtk_tree_view_new();
	gtk_widget_set_has_tooltip(priv->treeview, TRUE);
	gtk_tree_view_set_tooltip_column(GTK_TREE_VIEW(priv->treeview), GIGOLO_WINDOW_COL_TOOLTIP);
	gtk_tree_view_set_headers_clickable(GTK_TREE_VIEW(priv->treeview), TRUE);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(priv->treeview), FALSE);
	gtk_tree_sortable_set_sort_column_id(
		GTK_TREE_SORTABLE(priv->store), GIGOLO_WINDOW_COL_NAME, GTK_SORT_ASCENDING);

	sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(priv->treeview));
	gtk_tree_selection_set_mode(sel, GTK_SELECTION_SINGLE);

	if (gtk_check_version(2, 14, 0) == NULL)
	{
		renderer = gtk_cell_renderer_pixbuf_new();
		column = gtk_tree_view_column_new_with_attributes(NULL, renderer,
			"gicon", GIGOLO_WINDOW_COL_PIXBUF, NULL);
		gtk_tree_view_column_set_sort_indicator(column, FALSE);
		gtk_tree_view_column_set_resizable(column, TRUE);
		gtk_tree_view_append_column(GTK_TREE_VIEW(priv->treeview), column);
	}

	renderer = gtk_cell_renderer_toggle_new();
	column = gtk_tree_view_column_new_with_attributes(
		_("Connected"), renderer, "active", GIGOLO_WINDOW_COL_IS_MOUNTED, NULL);
	gtk_tree_view_column_set_sort_indicator(column, TRUE);
	gtk_tree_view_column_set_sort_column_id(column, GIGOLO_WINDOW_COL_IS_MOUNTED);
	gtk_tree_view_column_set_resizable(column, TRUE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(priv->treeview), column);
	g_signal_connect(renderer, "toggled", G_CALLBACK(tree_mounted_col_toggled_cb), window);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(
		_("Service Type"), renderer, "text", GIGOLO_WINDOW_COL_SCHEME, NULL);
	gtk_tree_view_column_set_sort_indicator(column, TRUE);
	gtk_tree_view_column_set_sort_column_id(column, GIGOLO_WINDOW_COL_SCHEME);
	gtk_tree_view_column_set_resizable(column, TRUE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(priv->treeview), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(
		_("Name"), renderer, "text", GIGOLO_WINDOW_COL_NAME, NULL);
	gtk_tree_view_column_set_sort_indicator(column, TRUE);
	gtk_tree_view_column_set_sort_column_id(column, GIGOLO_WINDOW_COL_NAME);
	gtk_tree_view_column_set_resizable(column, TRUE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(priv->treeview), column);

	gtk_tree_view_set_model(GTK_TREE_VIEW(priv->treeview), GTK_TREE_MODEL(priv->store));

	g_signal_connect(sel, "changed", G_CALLBACK(tree_selection_changed_cb), window);
	g_signal_connect(priv->treeview, "realize", G_CALLBACK(tree_realize_cb), window);
	g_signal_connect(priv->treeview, "button-press-event", G_CALLBACK(tree_button_press_event_cb), window);
	g_signal_connect(priv->treeview, "row-activated", G_CALLBACK(tree_row_activated_cb), window);
}
