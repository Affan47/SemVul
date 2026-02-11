vflist_select_cb(GtkTreeSelection *selection, GtkTreeModel *store, GtkTreePath *tpath,
				 gboolean path_currently_selected, gpointer data)
{
	ViewFile *vf = data;
	GtkTreeIter iter;

	if (!path_currently_selected &&
	    gtk_tree_model_get_iter(store, &iter, tpath))
		{
		gtk_tree_model_get(store, &iter, FILE_COLUMN_POINTER, &VFLIST(vf)->select_fd, -1);
		}
	else
		{
		VFLIST(vf)->select_fd = NULL;
		}

	if (vf->layout &&
	    !VFLIST(vf)->select_idle_id)
		{
		VFLIST(vf)->select_idle_id = g_idle_add(vflist_select_idle_cb, vf);
		}

	return TRUE;
}
