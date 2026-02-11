get_home_dir(void)
{
#ifdef G_OS_WIN32
	static char home_dir_utf16[MAX_PATH] = "";
	static gchar *home_dir_utf8 = NULL;
	if (home_dir_utf16[0] == '\0') {
		if (w32_shgetfolderpath
			    (NULL, CSIDL_APPDATA|CSIDL_FLAG_CREATE,
			     NULL, 0, home_dir_utf16) < 0)
				strcpy (home_dir_utf16, "C:\\Sylpheed");
		home_dir_utf8 = g_utf16_to_utf8 ((const gunichar *)home_dir_utf16, -1, NULL, NULL, NULL);
	}
	return home_dir_utf8;
#else
	static const gchar *homeenv = NULL;

	if (homeenv)
		return homeenv;

	if (!homeenv && g_getenv("HOME") != NULL)
		homeenv = g_strdup(g_getenv("HOME"));
	if (!homeenv)
		homeenv = g_get_home_dir();

	return homeenv;
#endif
}
