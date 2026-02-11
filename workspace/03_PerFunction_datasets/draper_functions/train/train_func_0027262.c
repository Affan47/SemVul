checkout_entry(struct cache_entry *ce, const struct checkout *state, char *topath)
{
	static char path[PATH_MAX + 1];
	struct stat st;
	int len = state->base_dir_len;

	if (topath)
		return write_entry(ce, topath, state, 1);

	memcpy(path, state->base_dir, len);
	strcpy(path + len, ce->name);

	if (!lstat(path, &st)) {
		unsigned changed = ce_match_stat(ce, &st, CE_MATCH_IGNORE_VALID);
		if (!changed)
			return 0;
		if (!state->force) {
			if (!state->quiet)
				fprintf(stderr, "git-checkout-index: %s already exists\n", path);
			return -1;
		}


		if (S_ISDIR(st.st_mode)) {

			if (S_ISGITLINK(ce->ce_mode))
				return 0;
			if (!state->force)
				return error("%s is a directory", path);
			remove_subtree(path);
		} else if (unlink(path))
			return error("unable to unlink old '%s' (%s)", path, strerror(errno));
	} else if (state->not_new)
		return 0;
	create_directories(path, state);
	return write_entry(ce, path, state, 0);
}
