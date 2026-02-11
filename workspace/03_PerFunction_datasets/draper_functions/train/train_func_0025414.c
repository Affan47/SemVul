gth_folder_tree_init (GthFolderTree *folder_tree)
{
	GtkTreeSelection *selection;

	folder_tree->priv = g_new0 (GthFolderTreePrivate, 1);
	folder_tree->priv->drag_source_enabled = FALSE;
	folder_tree->priv->dragging = FALSE;
	folder_tree->priv->drag_started = FALSE;
	folder_tree->priv->drag_target_list = NULL;
	folder_tree->priv->entry_points = g_hash_table_new_full (g_file_hash, (GEqualFunc) g_file_equal, g_object_unref, NULL);
	folder_tree->priv->recalc_entry_points = FALSE;
	folder_tree->priv->monitor.locations = g_hash_table_new_full (g_file_hash, (GEqualFunc) g_file_equal, g_object_unref, NULL);
	folder_tree->priv->monitor.sources = NULL;
	folder_tree->priv->monitor.update_id = 0;
	folder_tree->priv->icon_cache = gth_icon_cache_new (gtk_icon_theme_get_for_screen (gtk_widget_get_screen (GTK_WIDGET (folder_tree))),
							    _gtk_widget_lookup_for_size (GTK_WIDGET (folder_tree), GTK_ICON_SIZE_MENU));

	folder_tree->priv->tree_store = gtk_tree_store_new (NUM_COLUMNS,
							    PANGO_TYPE_STYLE,
							    PANGO_TYPE_WEIGHT,
							    GDK_TYPE_PIXBUF,
							    G_TYPE_INT,
							    G_TYPE_OBJECT,
							    G_TYPE_STRING,
							    G_TYPE_INT,
							    G_TYPE_STRING,
							    G_TYPE_BOOLEAN,
							    G_TYPE_BOOLEAN);
	gtk_tree_view_set_model (GTK_TREE_VIEW (folder_tree), GTK_TREE_MODEL (folder_tree->priv->tree_store));
	gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (folder_tree), FALSE);

	add_columns (folder_tree, GTK_TREE_VIEW (folder_tree));

	gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (folder_tree), FALSE);
	gtk_tree_view_set_enable_search (GTK_TREE_VIEW (folder_tree), TRUE);
	gtk_tree_view_set_search_column (GTK_TREE_VIEW (folder_tree), COLUMN_NAME);
	gtk_tree_sortable_set_sort_func (GTK_TREE_SORTABLE (folder_tree->priv->tree_store), COLUMN_NAME, column_name_compare_func, folder_tree, NULL);
	gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (folder_tree->priv->tree_store), COLUMN_NAME, GTK_SORT_ASCENDING);

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (folder_tree));
	gtk_tree_selection_set_mode (selection, GTK_SELECTION_SINGLE);
	g_signal_connect (selection,
			  "changed",
			  G_CALLBACK (selection_changed_cb),
			  folder_tree);


	g_signal_connect (folder_tree,
			  "popup-menu",
			  G_CALLBACK (popup_menu_cb),
			  folder_tree);
	g_signal_connect (folder_tree,
			  "button-press-event",
			  G_CALLBACK (button_press_cb),
			  folder_tree);
	g_signal_connect (folder_tree,
			  "motion-notify-event",
			  G_CALLBACK (motion_notify_event_cb),
			  folder_tree);
	g_signal_connect (folder_tree,
			  "button-release-event",
			  G_CALLBACK (button_release_event_cb),
			  folder_tree);
	g_signal_connect (folder_tree,
			  "row-activated",
			  G_CALLBACK (row_activated_cb),
			  folder_tree);
	g_signal_connect (folder_tree,
			  "row-expanded",
			  G_CALLBACK (row_expanded_cb),
			  folder_tree);
	g_signal_connect (folder_tree,
			  "row-collapsed",
			  G_CALLBACK (row_collapsed_cb),
			  folder_tree);
}
