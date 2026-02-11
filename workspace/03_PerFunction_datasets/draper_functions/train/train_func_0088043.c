_gth_file_store_compact_rows (GthFileStore *file_store)
{
	int i, j;

	for (i = 0, j = 0; i < file_store->priv->tot_rows; i++)
		if (file_store->priv->all_rows[i] != NULL) {
			file_store->priv->all_rows[j] = file_store->priv->all_rows[i];
			file_store->priv->all_rows[j]->abs_pos = j;
			j++;
		}
	file_store->priv->tot_rows = j;

	for (i = 0, j = 0; i < file_store->priv->num_rows; i++)
		if (file_store->priv->rows[i] != NULL) {
			file_store->priv->rows[j] = file_store->priv->rows[i];
			file_store->priv->rows[j]->pos = j;
			j++;
		}
	file_store->priv->num_rows = j;
}
