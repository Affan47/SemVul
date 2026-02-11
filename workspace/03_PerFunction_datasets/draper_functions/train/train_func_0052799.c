bookmarks_edited (GtkCellRenderer       *cell,
		  gchar                 *path_string,
		  gchar                 *new_text,
		  NemoPlacesSidebar *sidebar)
{
	GtkTreePath *path;
	GtkTreeIter iter;
	NemoBookmark *bookmark;
	int index;

	g_object_set (cell, "editable", FALSE, NULL);

	path = gtk_tree_path_new_from_string (path_string);
	gtk_tree_model_get_iter (GTK_TREE_MODEL (sidebar->store), &iter, path);
	gtk_tree_model_get (GTK_TREE_MODEL (sidebar->store), &iter,
		            PLACES_SIDEBAR_COLUMN_INDEX, &index,
		            -1);
	gtk_tree_path_free (path);
	bookmark = nemo_bookmark_list_item_at (sidebar->bookmarks, index);

	if (bookmark != NULL) {
		nemo_bookmark_set_custom_name (bookmark, new_text);
	}
}
