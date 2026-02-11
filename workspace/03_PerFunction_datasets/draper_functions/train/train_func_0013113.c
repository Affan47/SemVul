xdg_dir_get(const gchar *key, const gchar *fallback)
{
	gchar *dir = getenv(key);

	if (!dir || dir[0] == '\0')
		{
    		return g_build_filename(homedir(), fallback, NULL);
    		}

	return path_to_utf8(dir);
}
