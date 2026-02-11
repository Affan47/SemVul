get_destination_file (GthImportTask *self,
		      GthFileData   *file_data)
{
	GError *error = NULL;
	GFile  *destination;
	GFile  *destination_file;

	destination = gth_import_utils_get_file_destination (file_data,
							     self->priv->destination,
							     self->priv->subfolder_type,
							     self->priv->subfolder_format,
							     self->priv->single_subfolder,
							     self->priv->custom_format,
							     self->priv->event_name,
							     self->priv->import_start_time);
	if (! g_file_make_directory_with_parents (destination, gth_task_get_cancellable (GTH_TASK (self)), &error)) {
		if (! g_error_matches (error, G_IO_ERROR, G_IO_ERROR_EXISTS)) {
			gth_task_completed (GTH_TASK (self), error);
			return NULL;
		}
	}


	destination_file = _g_file_get_destination (file_data->file, NULL, destination);
	while (g_hash_table_lookup (self->priv->destinations, destination_file) != NULL) {
		GFile *tmp = destination_file;
		destination_file = _g_file_get_duplicated (tmp);
		g_object_unref (tmp);
	}
	g_hash_table_insert (self->priv->destinations, g_object_ref (destination_file), GINT_TO_POINTER (1));

	g_object_unref (destination);

	return destination_file;
}
