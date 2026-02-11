get_relative_path(const gchar *location, const gchar *path)
{
	gchar *dir;
	gint plen;
	gint dlen;

	if (!g_path_is_absolute(path))
	{
		return g_strdup(path);
	}

	dir = g_path_get_dirname(location);
	setptr(dir, normpath(dir));

	plen = strlen(path);
	dlen = strlen(dir);

	if (strstr(path, dir) == path)
	{
		if (plen > dlen)
		{
			setptr(dir, g_strdup(path + strlen(dir) + 1));
			return dir;
		}
		else if (plen == dlen)
		{
			return g_strdup("./");
		}
	}
	g_free(dir);
	return NULL;
}
