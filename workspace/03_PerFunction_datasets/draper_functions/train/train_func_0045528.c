gpk_update_viewer_find_iter_model_cb (GtkTreeModel *model,
				      GtkTreePath *path,
				      GtkTreeIter *iter,
				      const gchar *package_id)
{
	gchar *package_id_tmp = NULL;
	GtkTreePath **_path = NULL;
	gboolean ret = FALSE;

	gtk_tree_model_get (model, iter,
			    GPK_UPDATES_COLUMN_ID, &package_id_tmp,
			    -1);
	if (package_id_tmp == NULL)
		goto out;


	if (g_strcmp0 (package_id, package_id_tmp) == 0) {
		_path = (GtkTreePath **) g_object_get_data (G_OBJECT(model), "_path");
		*_path = gtk_tree_path_copy (path);
		ret = TRUE;
	}
out:
	g_free (package_id_tmp);
	return ret;
}
