panel_make_unique_desktop_path_from_name (const char *dir,
					  const char *name)
{
	int   num = 1;
	char *path = NULL;
#ifndef NAME_MAX

#ifdef MAXNAMLEN
#define NAME_MAX MAXNAMLEN
#else
#define NAME_MAX 255
#endif
#endif
	char  filename[NAME_MAX];


#define LENGTH_FOR_TMPFILE_EXT 7

	g_snprintf (filename,
		    sizeof (filename) - strlen (".desktop") - LENGTH_FOR_TMPFILE_EXT,
		    "%s", name);
	g_strlcat (filename, ".desktop", sizeof (filename));
	path = panel_make_full_path (dir, filename);
	if (!g_file_test (path, G_FILE_TEST_EXISTS))
		return path;
	g_free (path);

	while (TRUE) {
		char *buf;

		buf = g_strdup_printf ("-%d.desktop", num);
		g_snprintf (filename,
			    sizeof (filename) - strlen (buf) - LENGTH_FOR_TMPFILE_EXT,
			    "%s", name);
		g_strlcat (filename, buf, sizeof (filename));
		g_free (buf);

		path = panel_make_full_path (dir, filename);
		if (!g_file_test (path, G_FILE_TEST_EXISTS))
			return path;
		g_free (path);

		num++;
	}

	return NULL;
}
