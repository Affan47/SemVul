xrename (const gchar *oldp,
         const gchar *newp,
         const gchar *prefix,
         const gchar *suffix,
         gint missingok,
         GError **error)
{
	struct stat st;
	gchar *old, *new;
	gchar *basename;
	gint ret = -1;
	gint err = 0;

	basename = g_strconcat (oldp, suffix, NULL);
	old = g_build_filename (prefix, basename, NULL);
	g_free (basename);

	basename = g_strconcat (newp, suffix, NULL);
	new = g_build_filename (prefix, basename, NULL);
	g_free (basename);

	d (printf ("renaming %s%s to %s%s\n", oldp, suffix, newp, suffix));

	if (g_stat (old, &st) == -1) {
		if (missingok && errno == ENOENT) {
			ret = 0;
		} else {
			err = errno;
			ret = -1;
		}
	} else if ((!g_file_test (new, G_FILE_TEST_EXISTS) || g_remove (new) == 0) &&
		   g_rename (old, new) == 0) {
		ret = 0;
	} else {
		err = errno;
		ret = -1;
	}

	if (ret == -1) {
		g_set_error (
			error, G_IO_ERROR,
			g_io_error_from_errno (err),
			_("Could not rename folder %s to %s: %s"),
			old, new, g_strerror (err));
	}

	g_free (old);
	g_free (new);
	return ret;
}
