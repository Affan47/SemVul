claws_mailmbox_folder_create_parent(const gchar * path)
{
	if (!is_file_exist(path)) {
		gchar * new_path;

		new_path = g_path_get_dirname(path);
		if (new_path[strlen(new_path) - 1] == G_DIR_SEPARATOR)
			new_path[strlen(new_path) - 1] = '\0';

		if (!is_dir_exist(new_path))
			make_dir_hier(new_path);
		g_free(new_path);

	}
}
