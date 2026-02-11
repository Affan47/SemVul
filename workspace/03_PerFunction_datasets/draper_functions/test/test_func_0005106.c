magnatune_redownload_reload_db()
{
	GtkTreeIter iter;
	GtkTreeModel *model = gtk_tree_row_reference_get_model(magnatune_ref);
	GtkTreePath *path = gtk_tree_row_reference_get_path(magnatune_ref);
	if(path && gtk_tree_model_get_iter(model, &iter, path))
	{
		GtkTreeIter citer;
		while(gtk_tree_model_iter_children(model, &citer,&iter))
		{
			gtk_list_store_remove(GTK_LIST_STORE(model), &citer);
		}
		magnatune_download();
	}
	if(path)
		gtk_tree_path_free(path);
}
