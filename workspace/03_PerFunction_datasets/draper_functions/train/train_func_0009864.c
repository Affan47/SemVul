e_mail_label_list_store_lookup (EMailLabelListStore *store,
                                const gchar *tag,
                                GtkTreeIter *iter)
{
	GtkTreeRowReference *reference;
	GHashTable *tag_index;
	GtkTreeModel *model;
	GtkTreePath *path;

	g_return_val_if_fail (E_IS_MAIL_LABEL_LIST_STORE (store), FALSE);
	g_return_val_if_fail (tag != NULL, FALSE);
	g_return_val_if_fail (iter != NULL, FALSE);

	tag_index = store->priv->tag_index;
	reference = g_hash_table_lookup (tag_index, tag);

	if (reference == NULL)
		return FALSE;

	if (!gtk_tree_row_reference_valid (reference)) {

		g_hash_table_remove (tag_index, tag);
		return FALSE;
	}

	model = gtk_tree_row_reference_get_model (reference);
	path = gtk_tree_row_reference_get_path (reference);
	gtk_tree_model_get_iter (model, iter, path);
	gtk_tree_path_free (path);

	return TRUE;
}
