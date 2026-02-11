gth_selections_manager_file_exists (int    n_selection,
				    GFile *file)
{
	GthSelectionsManager *self;
	gboolean             result;

	if ((n_selection <= 0) || (n_selection > GTH_SELECTIONS_MANAGER_N_SELECTIONS))
		return FALSE;

	self = gth_selections_manager_get_default ();
	g_mutex_lock (&self->priv->mutex);

	result = (g_hash_table_lookup (self->priv->files_hash[n_selection - 1], file) != NULL);

	g_mutex_unlock (&self->priv->mutex);

	return result;
}
