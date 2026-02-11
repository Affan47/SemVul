create_home_directory()  {

	gchar *path;
	struct stat s;

#ifndef WIN32
	path = g_strconcat( getenv("HOME"), "/", ".", PACKAGE, "/", NULL);
#else
	HKEY hKey;
	TCHAR home[PATH_MAX];
	DWORD size = PATH_MAX;

	if (RegOpenKeyEx(HKEY_CURRENT_USER,
		"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",
		0, KEY_READ, &hKey) != ERROR_SUCCESS ||
		RegQueryValueEx(hKey, "Personal", NULL, NULL, (LPBYTE)home, &size) != ERROR_SUCCESS ||
		RegCloseKey(hKey) != ERROR_SUCCESS) {
			path = g_strconcat(PACKAGE, "/", NULL);
	} else {
		path = g_strconcat(home, "/", PACKAGE, "/", NULL);
	}
#endif
	global->path_home = g_strdup(path);
	if(stat(path, &s) < 0)  {

		mkdir(path, 0777);
		if(stat(path, &s) < 0)  {

			g_free(path);
			return FALSE;
		}
	}
	g_free(path);

	path = g_strconcat( global->path_home, "themes/", NULL);
	if(stat(path, &s) < 0)  {

		mkdir(path, 0777);
		if(stat(path, &s) < 0)  {

			g_free(path);
			return FALSE;
		}
	}
	g_free(path);

	return TRUE;
}
