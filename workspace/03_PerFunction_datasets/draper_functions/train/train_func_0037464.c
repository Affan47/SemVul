php_glob_stream_path_split(glob_s_t *pglob, char *path, int get_path, char **p_file TSRMLS_DC)
{
	char *pos, *gpath = path;

	if ((pos = strrchr(path, '/')) != NULL) {
		path = pos+1;
	}
#if defined(PHP_WIN32) || defined(NETWARE)
	if ((pos = strrchr(path, '\\')) != NULL) {
		path = pos+1;
	}
#endif

	*p_file = path;

	if (get_path) {
		if (pglob->path) {
			efree(pglob->path);
		}
		if (path != gpath) {
			path--;
		}
		pglob->path_len = path - gpath;
		pglob->path = estrndup(gpath, pglob->path_len);
	}
}
