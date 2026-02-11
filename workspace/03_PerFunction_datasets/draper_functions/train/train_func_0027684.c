get_bookmarks_for_editor (AnjutaBookmarks* bookmarks, IAnjutaEditor* editor)
{
	AnjutaBookmarksPrivate* priv = BOOKMARKS_GET_PRIVATE(bookmarks);
	GList* marks = NULL;
	GtkTreeIter iter;
	GFile* file;
	if (!gtk_tree_model_get_iter_first (priv->model, &iter))
		return NULL;
	file = ianjuta_file_get_file (IANJUTA_FILE(editor), NULL);
	if (!file)
		return NULL;
	do
	{
		GFile* bookmark_file;
		gint line;
		gtk_tree_model_get (priv->model,
							&iter,
							COLUMN_FILE, &bookmark_file,
							COLUMN_LINE, &line,
							-1);
		if (g_file_equal (file, bookmark_file))
			marks = g_list_insert_sorted (marks, GINT_TO_POINTER(line), line_compare);
		g_object_unref (bookmark_file);
	}
	while (gtk_tree_model_iter_next (priv->model, &iter));
	g_object_unref (file);

	return marks;
}
