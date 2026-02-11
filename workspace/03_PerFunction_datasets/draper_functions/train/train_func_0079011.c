gth_folder_tree_loading_children (GthFolderTree *folder_tree,
				  GFile         *parent)
{
	GtkTreeIter  parent_iter;
	GtkTreeIter *p_parent_iter;
	GtkTreeIter  iter;
	gboolean     valid_iter;

	if (g_file_equal (parent, folder_tree->priv->root))
		p_parent_iter = NULL;
	else if (gth_folder_tree_get_iter (folder_tree, parent, &parent_iter, NULL))
		p_parent_iter = &parent_iter;
	else
		return;

	_gth_folder_tree_add_loading_item (folder_tree, p_parent_iter, FALSE);


	gtk_tree_model_iter_children (GTK_TREE_MODEL (folder_tree->priv->tree_store), &iter, p_parent_iter);
	do {
		EntryType file_entry_type;

		gtk_tree_model_get (GTK_TREE_MODEL (folder_tree->priv->tree_store), &iter,
				    COLUMN_TYPE, &file_entry_type,
				    -1);

		if (file_entry_type != ENTRY_TYPE_LOADING)
			valid_iter = gtk_tree_store_remove (folder_tree->priv->tree_store, &iter);
		else
			valid_iter = gtk_tree_model_iter_next (GTK_TREE_MODEL (folder_tree->priv->tree_store), &iter);
	}
	while (valid_iter);

	emit_fake_motion_notify_event (folder_tree);
}
