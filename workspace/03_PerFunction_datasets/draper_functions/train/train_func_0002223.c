combo_action_cell_changed (GtkCellRendererCombo *cell,
                           const gchar          *path_string,
                           GtkTreeIter          *new_iter,
                           CcWacomPage          *page)
{
	GtkTreeView          *tree_view;
	GtkTreePath          *path;
	GtkTreeModel         *model;
	CcWacomPagePrivate   *priv;
	GsdWacomActionType    type;
	GtkTreeIter           iter;
	GsdWacomTabletButton *button;

	priv = page->priv;
	tree_view = GTK_TREE_VIEW (MWID("shortcut_treeview"));
	model = gtk_tree_view_get_model (tree_view);
	path = gtk_tree_path_new_from_string (path_string);

	gtk_tree_model_get (GTK_TREE_MODEL (priv->action_store), new_iter, ACTION_TYPE_COLUMN, &type, -1);
	gtk_tree_model_get_iter (model, &iter, path);
	gtk_list_store_set (GTK_LIST_STORE (model), &iter, MAPPING_TYPE_COLUMN, WACOM_C(action_table[type].action_name), -1);
	gtk_tree_path_free (path);

	gtk_tree_model_get (model, &iter, MAPPING_BUTTON_COLUMN, &button, -1);
	if (button == NULL)
		return;
	if (button->settings == NULL)
		return;
	g_settings_set_enum (button->settings, ACTION_TYPE_KEY, type);

	gtk_widget_grab_focus (GTK_WIDGET (tree_view));
}
