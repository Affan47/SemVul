add_file_to_catalog (GthOrganizeTask *self,
		     GthCatalog      *catalog,
		     const char      *catalog_key,
		     GthFileData     *file_data)
{
	GtkTreeIter iter;
	int         n = 0;

	if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (self->priv->results_liststore), &iter)) {
		do {
			char *k;

			gtk_tree_model_get (GTK_TREE_MODEL (self->priv->results_liststore),
					    &iter,
					    KEY_COLUMN, &k,
					    CARDINALITY_COLUMN, &n,
					    -1);
			if (g_strcmp0 (k, catalog_key) == 0) {
				gtk_list_store_set (self->priv->results_liststore, &iter,
						    CARDINALITY_COLUMN, n + 1,
						    -1);
				self->priv->n_files++;

				g_free (k);
				break;
			}

			g_free (k);
		}
		while (gtk_tree_model_iter_next (GTK_TREE_MODEL (self->priv->results_liststore), &iter));
	}

	gth_catalog_insert_file (catalog, file_data->file, -1);
}
