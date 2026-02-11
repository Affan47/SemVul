attachment_update_progress_columns_idle_cb (gpointer weak_ref)
{
	EAttachment *attachment;
	GtkTreeRowReference *reference;
	GtkTreeModel *model;
	GtkTreePath *path;
	GtkTreeIter iter;
	gboolean loading;
	gboolean saving;
	gint percent;

	attachment = g_weak_ref_get (weak_ref);
	if (attachment == NULL)
		goto exit;

	g_mutex_lock (&attachment->priv->idle_lock);
	attachment->priv->update_progress_columns_idle_id = 0;
	g_mutex_unlock (&attachment->priv->idle_lock);

	reference = e_attachment_get_reference (attachment);
	if (!gtk_tree_row_reference_valid (reference))
		goto exit;

	model = gtk_tree_row_reference_get_model (reference);
	path = gtk_tree_row_reference_get_path (reference);
	gtk_tree_model_get_iter (model, &iter, path);
	gtk_tree_path_free (path);


	percent = e_attachment_get_percent (attachment);
	loading = e_attachment_get_loading (attachment) && (percent > 0);
	saving = e_attachment_get_saving (attachment) && (percent > 0);

	gtk_list_store_set (
		GTK_LIST_STORE (model), &iter,
		E_ATTACHMENT_STORE_COLUMN_LOADING, loading,
		E_ATTACHMENT_STORE_COLUMN_PERCENT, percent,
		E_ATTACHMENT_STORE_COLUMN_SAVING, saving,
		-1);

exit:
	g_clear_object (&attachment);

	return FALSE;
}
