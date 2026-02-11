prefs_themes_get_theme_stats(const gchar *dirname)
{
	gchar   *stats;
	DirInfo *dinfo;

	dinfo = g_new0(DirInfo, 1);

	prefs_themes_foreach_file(dirname, prefs_themes_file_stats, dinfo);
	stats = g_strdup_printf(_("%d files (%d icons), size: %s"),
				dinfo->files, dinfo->pixms, to_human_readable((goffset)dinfo->bytes));

	g_free(dinfo);
	return stats;
}
