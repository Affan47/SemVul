filetypes_get_filename(GeanyFiletype *ft, gboolean user)
{
	gchar *ext = filetypes_get_conf_extension(ft);
	gchar *base_name = g_strconcat("filetypes.", ext, NULL);
	gchar *file_name;

	if (user)
		file_name = g_build_filename(app->configdir, GEANY_FILEDEFS_SUBDIR, base_name, NULL);
	else
		file_name = g_build_filename(app->datadir, base_name, NULL);

	g_free(ext);
	g_free(base_name);

	return file_name;
}
