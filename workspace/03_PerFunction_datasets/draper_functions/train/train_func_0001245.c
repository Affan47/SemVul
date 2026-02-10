read_metadata_info_ready_cb (GList    *files,
			     GError   *error,
			     gpointer  user_data)
{
	ReadMetadataOpData *read_metadata = user_data;
	GthFileData        *result;
	GFile              *gio_file;

	if (error != NULL) {
		read_metadata->callback (G_OBJECT (read_metadata->file_source), error, read_metadata->data);
		read_metadata_free (read_metadata);
		return;
	}

	result = files->data;
	g_file_info_copy_into (result->info, read_metadata->file_data->info);
	update_file_info (read_metadata->file_source, read_metadata->file_data->file, read_metadata->file_data->info);

	gio_file = gth_catalog_file_to_gio_file (read_metadata->file_data->file);
	gth_catalog_load_from_file_async (gio_file,
					  gth_file_source_get_cancellable (read_metadata->file_source),
					  read_metadata_catalog_ready_cb,
					  read_metadata);

	g_object_unref (gio_file);
}
