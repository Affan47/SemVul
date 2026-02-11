_g_file_new_user_config_subdir (const char *child_name,
			        gboolean    create_child)
{
	char   *full_path;
	GFile  *file;
	GError *error = NULL;

	full_path = g_strconcat (g_get_user_config_dir (), "/", child_name, NULL);
	file = g_file_new_for_path (full_path);
	g_free (full_path);

	if  (create_child && ! _g_file_make_directory_tree (file, 0700, &error)) {
		g_warning ("%s", error->message);
		g_error_free (error);
		g_object_unref (file);
		file = NULL;
	}

	return file;
}
