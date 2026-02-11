install_scripts (const gchar *into_dir)
{
	GDir *dir;
	GError *err = NULL;
	gchar path[XMMS_PATH_MAX];
	const gchar *f;
	gchar *s;

	s = strrchr (into_dir, G_DIR_SEPARATOR);
	if (!s)
		return;

	s++;

	g_snprintf (path, XMMS_PATH_MAX, "%s/scripts/%s", SHAREDDIR, s);
	xmms_log_info ("Installing scripts from %s", path);
	dir = g_dir_open (path, 0, &err);
	if (!dir) {
		xmms_log_error ("Global script directory not found");
		return;
	}

	while ((f = g_dir_read_name (dir))) {
		gchar *source = g_strdup_printf ("%s/%s", path, f);
		gchar *dest = g_strdup_printf ("%s/%s", into_dir, f);
		if (!xmms_symlink_file (source, dest)) {
			g_free (source);
			g_free (dest);
			break;
		}
		g_free (source);
		g_free (dest);
	}

	g_dir_close (dir);
}
