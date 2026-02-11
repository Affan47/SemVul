hostiles_retrieve_from_file(FILE *f, hostiles_t which,
	const char *path, const char *filename)
{
	char *pathname;

	g_assert(f);
	g_assert(path);
	g_assert(filename);
	g_assert(UNSIGNED(which) < NUM_HOSTILES);

	pathname = make_pathname(path, filename);
	watcher_register(pathname, hostiles_changed, GUINT_TO_POINTER(which));
	HFREE_NULL(pathname);
	hostiles_load(f, which);
}
