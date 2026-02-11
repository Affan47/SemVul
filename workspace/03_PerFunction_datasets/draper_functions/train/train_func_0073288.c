gm_mcp_userlist_view_create_userlist(GmMcpUserlistView *view) {
	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	GtkTreeModel *model = gm_mcp_userlist_view_model_create(view);
	GtkWidget *tree_view = gtk_tree_view_new_with_model(model);
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;

	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled_window),
			GTK_SHADOW_IN);

	GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrolled_window));
	g_signal_connect(adj, "changed", G_CALLBACK(on_adj_changed), view);

	gtk_widget_set_size_request(scrolled_window, 150, -1);
	gtk_widget_set_size_request(tree_view, 150, -1);

	gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);

	renderer = gtk_cell_renderer_pixbuf_new();
	column = gtk_tree_view_column_new_with_attributes(_("I"), renderer,
			"pixbuf", GM_USERLIST_ICON, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
	gtk_tree_view_column_set_min_width(column, 30);

	renderer = gm_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(_("Name"), renderer,
			"name", GM_USERLIST_NAME, "status", GM_USERLIST_STATUS, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

	gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(model),
			GTK_TREE_SORTABLE_DEFAULT_SORT_COLUMN_ID, GTK_SORT_ASCENDING);
	gtk_tree_sortable_set_default_sort_func(GTK_TREE_SORTABLE(model),
			(GtkTreeIterCompareFunc)gm_mcp_userlist_view_sort_func, view, NULL);

	GTK_WIDGET_UNSET_FLAGS(GTK_WIDGET(tree_view), GTK_CAN_FOCUS);

	gtk_widget_modify_base(GTK_WIDGET(tree_view), GTK_STATE_ACTIVE,
			&(GTK_WIDGET(tree_view)->style->base[GTK_STATE_SELECTED]));
	gtk_widget_modify_text(GTK_WIDGET(tree_view), GTK_STATE_ACTIVE,
			&(GTK_WIDGET(tree_view)->style->text[GTK_STATE_SELECTED]));

	gtk_tree_view_columns_autosize(GTK_TREE_VIEW(tree_view));
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree_view), FALSE);

	view->tree_view = GTK_TREE_VIEW(tree_view);
	view->scrolled_window = GTK_SCROLLED_WINDOW(scrolled_window);

	return scrolled_window;
}
