tm_get_real_path(const gchar *file_name)
{
	if (file_name)
	{
		gsize len = get_path_max(file_name) + 1;
		gchar *path = g_malloc0(len);

		if (realpath(file_name, path))
			return path;
		else
			g_free(path);
	}
	return NULL;
}
