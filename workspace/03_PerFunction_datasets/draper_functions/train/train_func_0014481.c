panel_addto_make_application_model (PanelAddtoDialog *dialog)
{
	GtkTreeStore      *store;
	GMenuTree          *tree;
	GMenuTreeDirectory *root;

	if (dialog->filter_application_model != NULL)
		return;

	store = gtk_tree_store_new (NUMBER_COLUMNS,
				    G_TYPE_ICON,
				    G_TYPE_STRING,
				    G_TYPE_POINTER,
				    G_TYPE_STRING);

	tree = gmenu_tree_new ("gnome-flashback-applications.menu", GMENU_TREE_FLAGS_SORT_DISPLAY_NAME);

	if (!gmenu_tree_load_sync (tree, NULL)) {
		g_object_unref (tree);
		tree = NULL;
	}

	if (tree != NULL && (root = gmenu_tree_get_root_directory (tree))) {
		panel_addto_make_application_list (&dialog->application_list,
						   root, "gnome-flashback-applications.menu",
						   PANEL_ADDTO_MENU_SHOW_ALL);
		panel_addto_populate_application_model (store, NULL, dialog->application_list);

		gmenu_tree_item_unref (root);
	}

	if (tree != NULL)
		g_object_unref (tree);

	tree = gmenu_tree_new ("gnomecc.menu", GMENU_TREE_FLAGS_SORT_DISPLAY_NAME);

	if (!gmenu_tree_load_sync (tree, NULL)) {
		g_object_unref (tree);
		tree = NULL;
	}

	if (tree != NULL && (root = gmenu_tree_get_root_directory (tree))) {
		GtkTreeIter iter;

		gtk_tree_store_append (store, &iter, NULL);
		gtk_tree_store_set (store, &iter,
				    COLUMN_ICON, NULL,
				    COLUMN_TEXT, NULL,
				    COLUMN_DATA, NULL,
				    COLUMN_SEARCH, NULL,
				    -1);


		panel_addto_make_application_list (&dialog->settings_list,
						   root, "gnomecc.menu",
						   PANEL_ADDTO_MENU_SHOW_DIRECTORIES);
		panel_addto_populate_application_model (store, NULL,
							dialog->settings_list);

		gmenu_tree_item_unref (root);
	}

	if (tree != NULL)
		g_object_unref (tree);

	dialog->application_model = GTK_TREE_MODEL (store);
	dialog->filter_application_model = gtk_tree_model_filter_new (GTK_TREE_MODEL (dialog->application_model),
								      NULL);
	gtk_tree_model_filter_set_visible_func (GTK_TREE_MODEL_FILTER (dialog->filter_application_model),
						panel_addto_filter_func,
						dialog, NULL);
}
