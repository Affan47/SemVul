editor_add_desktop_dir(GList *list, const gchar *path)
{
	DIR *dp;
	struct dirent *dir;
	gchar *pathl;

	pathl = path_from_utf8(path);
	dp = opendir(pathl);
	g_free(pathl);
	if (!dp)
		{

		return list;
		}
	while ((dir = readdir(dp)) != NULL)
		{
		gchar *namel = dir->d_name;

		if (g_str_has_suffix(namel, ".desktop"))
			{
			gchar *name = path_to_utf8(namel);
			gchar *dpath = g_build_filename(path, name, NULL);
			list = g_list_prepend(list, dpath);
			g_free(name);
			}
		}
	closedir(dp);
	return list;
}
