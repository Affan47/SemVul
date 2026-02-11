get_local_copy_for_file (GFile *remote_file)
{
	char  *temp_dir;
	GFile *local_copy = NULL;

	temp_dir = _g_path_get_temp_work_dir (NULL);
	if (temp_dir != NULL) {
		char  *archive_name;
		char  *local_path;

		archive_name = g_file_get_basename (remote_file);
		local_path = g_build_filename (temp_dir, archive_name, NULL);
		local_copy = g_file_new_for_path (local_path);

		g_free (local_path);
		g_free (archive_name);
	}
	g_free (temp_dir);

	return local_copy;
}
