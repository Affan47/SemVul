_e2_fileview_cursor_change_cb (GtkTreeView *treeview, ViewInfo *view)
{
	printd (DEBUG, "callback: cursor changed");
	GtkTreePath *path;
	gtk_tree_view_get_cursor (treeview, &path, NULL);
	if (path != NULL)
	{
		view->row = *gtk_tree_path_get_indices (path);
		gtk_tree_path_free (path);
	}
	printd (DEBUG, "focus row is %d", view->row);
	return FALSE;
}
