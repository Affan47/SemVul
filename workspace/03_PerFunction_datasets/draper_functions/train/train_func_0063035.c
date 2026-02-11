get_path_in_cache(const char *name, const char *suffix)
{
	int i;
	char *path;
	char *result;

	path = x_strdup(cache_dir);
	for (i = 0; i < nlevels; ++i) {
		char *p;
		x_asprintf(&p, "%s/%c", path, name[i]);
		free(path);
		path = p;
		if (create_dir(path) != 0) {
			cc_log("Failed to create %s", path);
			failed();
		}
	}
	x_asprintf(&result, "%s/%s%s", path, name + nlevels, suffix);
	free(path);
	return result;
}
