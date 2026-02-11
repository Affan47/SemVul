cb_delete(GtkWidget *widget)
	{
	GtkTreeModel	*model;
	GtkTreePath		*path;
	GtkTreeIter		iter;
	FSmon			*fs;

	if (!row_reference)
		return;
	model = gtk_tree_view_get_model(treeview);
	path = gtk_tree_row_reference_get_path(row_reference);
	gtk_tree_model_get_iter(model, &iter, path);

	gtk_tree_model_get(model, &iter, FSMON_COLUMN, &fs, -1);
	gkrellm_alert_destroy(&fs->alert);

	gtk_tree_store_remove(GTK_TREE_STORE(model), &iter);
	reset_entries(FALSE);
	sync_fs_panels();
	}
