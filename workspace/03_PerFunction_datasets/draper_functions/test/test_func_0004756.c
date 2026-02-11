compute_base_path (const char *base_dir,
		   const char *path,
		   gboolean    junk_paths,
		   gboolean    can_junk_paths)
{
	int         base_dir_len = strlen (base_dir);
	int         path_len = strlen (path);
	const char *base_path;
	char       *name_end;
	char       *new_path;

	if (junk_paths) {
		if (can_junk_paths)
			new_path = g_strdup (_g_path_get_basename (path));
		else
			new_path = g_strdup (path);


		return new_path;
	}

	if (path_len <= base_dir_len)
		return NULL;

	base_path = path + base_dir_len;
	if (path[0] != '/')
		base_path -= 1;
	name_end = strchr (base_path, '/');

	if (name_end == NULL)
		new_path = g_strdup (path);
	else {
		int name_len = name_end - path;
		new_path = g_strndup (path, name_len);
	}


	return new_path;
}
