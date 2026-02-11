get_repo_path(const char *repo, int *is_bundle)
{
	static char *suffix[] = { "/.git", ".git", "" };
	static char *bundle_suffix[] = { ".bundle", "" };
	struct stat st;
	int i;

	for (i = 0; i < ARRAY_SIZE(suffix); i++) {
		const char *path;
		path = mkpath("%s%s", repo, suffix[i]);
		if (is_directory(path)) {
			*is_bundle = 0;
			return xstrdup(absolute_path(path));
		}
	}

	for (i = 0; i < ARRAY_SIZE(bundle_suffix); i++) {
		const char *path;
		path = mkpath("%s%s", repo, bundle_suffix[i]);
		if (!stat(path, &st) && S_ISREG(st.st_mode)) {
			*is_bundle = 1;
			return xstrdup(absolute_path(path));
		}
	}

	return NULL;
}
