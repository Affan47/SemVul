test_cwd ()
{
	char *dir = g_get_current_dir ();
#ifdef G_OS_WIN32
	const gchar *newdir = "C:\\Windows";
#else
	const gchar *newdir = "/bin";
#endif

	if (dir == NULL)
		return FAILED ("No current directory?");
	g_free (dir);

	if (chdir (newdir) == -1)
		return FAILED ("No %s?", newdir);

	dir = g_get_current_dir ();
	if (strcmp (dir, newdir) != 0)
		return FAILED("Did not go to %s?", newdir);
	g_free (dir);

	return OK;
}
