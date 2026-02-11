is_absolute_path(const char *path)
{
	g_assert(path != NULL);

	if (is_dir_separator(path[0]))
		return TRUE;


	return is_running_on_mingw() &&
			is_ascii_alpha(path[0]) &&
			':' == path[1] &&
			is_dir_separator(path[2]);
}
