prefs_rc_is_readonly(const gchar * rcfile)
{
	gboolean result;
	gchar * rcpath;

	if (rcfile == NULL)
		return TRUE;

	rcpath = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S, rcfile, NULL);
	result = prefs_is_readonly(rcpath);
	g_free(rcpath);

	return result;
}
