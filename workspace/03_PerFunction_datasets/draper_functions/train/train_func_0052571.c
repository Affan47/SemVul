cache_reaper_scan_directory (ECacheReaper *extension,
                             GFile *base_directory,
                             GFile *trash_directory)
{
	GFileEnumerator *file_enumerator;
	ESourceRegistryServer *server;
	GFileInfo *file_info;
	GError *error = NULL;

	server = cache_reaper_get_server (extension);

	file_enumerator = g_file_enumerate_children (
		base_directory,
		G_FILE_ATTRIBUTE_STANDARD_NAME,
		G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
		NULL, &error);

	if (error != NULL) {
		g_warn_if_fail (file_enumerator == NULL);
		goto exit;
	}

	g_return_if_fail (G_IS_FILE_ENUMERATOR (file_enumerator));

	file_info = g_file_enumerator_next_file (
		file_enumerator, NULL, &error);

	while (file_info != NULL) {
		ESource *source;
		const gchar *name;

		name = g_file_info_get_name (file_info);


		if (g_strcmp0 (name, TRASH_DIRECTORY_NAME) == 0)
			goto next;


		if (g_strcmp0 (name, "system") == 0)
			goto next;

		source = e_source_registry_server_ref_source (server, name);

		if (source == NULL) {
			GFile *source_directory;
			GFile *target_directory;

			source_directory = g_file_get_child (
				base_directory, name);
			target_directory = g_file_get_child (
				trash_directory, name);

			cache_reaper_move_directory (
				source_directory, target_directory);

			g_object_unref (source_directory);
			g_object_unref (target_directory);
		} else {
			g_object_unref (source);
		}

next:
		g_object_unref (file_info);

		file_info = g_file_enumerator_next_file (
			file_enumerator, NULL, &error);
	}

	g_object_unref (file_enumerator);

exit:
	if (error != NULL) {
		gchar *path;

		path = g_file_get_path (base_directory);
		g_warning ("Failed to scan '%s': %s", path, error->message);
		g_free (path);

		g_error_free (error);
	}
}
