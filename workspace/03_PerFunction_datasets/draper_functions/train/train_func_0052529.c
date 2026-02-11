source_registry_server_create_source (ESourceRegistryServer *server,
                                      const gchar *uid,
                                      const gchar *data,
                                      GError **error)
{
	ESource *source = NULL;
	GFile *file;
	GFile *parent;
	GKeyFile *key_file;
	gboolean success;
	gsize length;
	GError *local_error = NULL;

	g_return_val_if_fail (uid != NULL, FALSE);
	g_return_val_if_fail (data != NULL, FALSE);

	length = strlen (data);


	key_file = g_key_file_new ();
	success = g_key_file_load_from_data (
		key_file, data, length, G_KEY_FILE_NONE, error);
	g_key_file_free (key_file);

	if (!success)
		return FALSE;


	source = e_source_registry_server_ref_source (server, uid);
	if (source != NULL) {
		g_set_error (
			error, G_IO_ERROR, G_IO_ERROR_EXISTS,
			_("UID '%s' is already in use"), uid);
		g_object_unref (source);
		return FALSE;
	}

	file = e_server_side_source_new_user_file (uid);


	parent = g_file_get_parent (file);
	g_file_make_directory_with_parents (parent, NULL, &local_error);
	g_object_unref (parent);

	if (g_error_matches (local_error, G_IO_ERROR, G_IO_ERROR_EXISTS))
		g_clear_error (&local_error);

	if (local_error != NULL) {
		g_propagate_error (error, local_error);
		success = FALSE;
	}


	if (success)
		success = g_file_replace_contents (
			file, data, length, NULL, FALSE,
			G_FILE_CREATE_PRIVATE, NULL, NULL, error);

	if (success) {
		ESourcePermissionFlags flags;


		flags = E_SOURCE_PERMISSION_WRITABLE |
			E_SOURCE_PERMISSION_REMOVABLE;

		source = e_source_registry_server_load_file (
			server, file, flags, error);


		if (source != NULL)
			g_object_unref (source);
		else
			success = FALSE;
	}

	g_object_unref (file);

	return success;
}
