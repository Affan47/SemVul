tree_fill(GigoloBookmarkDialog *dialog)
{
	guint i;
	GigoloBookmark *bm;
	GigoloBookmarkDialogPrivate *priv = GIGOLO_BOOKMARK_DIALOG_GET_PRIVATE(dialog);
	GigoloBookmarkList *bml = gigolo_settings_get_bookmarks(
		gigolo_window_get_settings(GIGOLO_WINDOW(priv->parent)));
	GtkTreeIter iter;

	for (i = 0; i < bml->len; i++)
	{
		bm = g_ptr_array_index(bml, i);

		gtk_list_store_append(priv->store, &iter);
		update_row_in_model(dialog, &iter, bm);
	}
}
