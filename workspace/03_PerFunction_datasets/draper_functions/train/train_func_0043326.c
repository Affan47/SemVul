searchLibpaco()
{
	string libpath(LIBDIR "/libpaco-log.so");
	struct stat s;

	if (!stat(libpath.c_str(), &s))
		return libpath;

	glob_t g;
	memset(&g, 0, sizeof(g));

	if (!glob(LIBDIR "/libpaco-log.so.[0-9]*", GLOB_NOSORT,0, &g) && g.gl_pathc)
		libpath = g.gl_pathv[0];

	globfree(&g);

	return libpath;
}
