check_arg_is_absolute_nss_path(const char *path)
{
	if (strncmp(path, "sql:", 4) == 0) {
		path += 4;
	} else
	if (strncmp(path, "dbm:", 4) == 0) {
		path += 4;
	} else
	if (strncmp(path, "rdb:", 4) == 0) {
		path += 4;
	} else
	if (strncmp(path, "extern:", 7) == 0) {
		path += 7;
	}
	if (path[0] == '/') {
		return 0;
	} else {
		errno = EINVAL;
		return -1;
	}
}
