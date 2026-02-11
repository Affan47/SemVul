is_regular(const char *pathname)
{
	filestat_t st;

	g_assert(pathname);
	return 0 == stat(pathname, &st) && S_ISREG(st.st_mode);
}
