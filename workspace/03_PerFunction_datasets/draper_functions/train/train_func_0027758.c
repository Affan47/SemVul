create_cellrenderertoggle_toggled_cb (GtkCellRendererToggle *cell_renderer,
				      char                  *path,
				      gpointer               user_data)
{
	GthOrganizeTask *self = user_data;
	GtkTreePath     *tpath;
	GtkTreeIter      iter;

	tpath = gtk_tree_path_new_from_string (path);
	if (tpath == NULL)
		return;

	if (gtk_tree_model_get_iter (GTK_TREE_MODEL (self->priv->results_liststore), &iter, tpath)) {
		gboolean create;

		gtk_tree_model_get (GTK_TREE_MODEL (self->priv->results_liststore), &iter,
				    CREATE_CATALOG_COLUMN, &create,
				    -1);
		gtk_list_store_set (self->priv->results_liststore, &iter,
				    CREATE_CATALOG_COLUMN, ! create,
				    -1);
	}

	gtk_tree_path_free (tpath);
}
