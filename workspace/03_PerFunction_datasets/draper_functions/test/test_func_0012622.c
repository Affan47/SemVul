gth_file_store_find_visible (GthFileStore *file_store,
			     GFile        *file,
			     GtkTreeIter  *iter)
{
	gboolean found = FALSE;
	int      i;

	for (i = 0; i < file_store->priv->num_rows; i++) {
		GthFileRow *row = file_store->priv->rows[i];

		if (row == NULL)
			continue;

		if (g_file_equal (row->file_data->file, file)) {
			if (iter != NULL) {
				iter->stamp = file_store->priv->stamp;
				iter->user_data = row;
			}
			found = TRUE;
			break;
		}
	}

	return found;
}
