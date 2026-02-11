checkout_paths(struct tree *source_tree, const char **pathspec)
{
	int pos;
	struct checkout state;
	static char *ps_matched;
	unsigned char rev[20];
	int flag;
	struct commit *head;
	int errs = 0;

	int newfd;
	struct lock_file *lock_file = xcalloc(1, sizeof(struct lock_file));

	newfd = hold_locked_index(lock_file, 1);
	read_cache();

	if (source_tree)
		read_tree_some(source_tree, pathspec);

	for (pos = 0; pathspec[pos]; pos++)
		;
	ps_matched = xcalloc(1, pos);

	for (pos = 0; pos < active_nr; pos++) {
		struct cache_entry *ce = active_cache[pos];
		pathspec_match(pathspec, ps_matched, ce->name, 0);
	}

	if (report_path_error(ps_matched, pathspec, 0))
		return 1;


	memset(&state, 0, sizeof(state));
	state.force = 1;
	state.refresh_cache = 1;
	for (pos = 0; pos < active_nr; pos++) {
		struct cache_entry *ce = active_cache[pos];
		if (pathspec_match(pathspec, NULL, ce->name, 0)) {
			errs |= checkout_entry(ce, &state, NULL);
		}
	}

	if (write_cache(newfd, active_cache, active_nr) ||
	    commit_locked_index(lock_file))
		die("unable to write new index file");

	resolve_ref("HEAD", rev, 0, &flag);
	head = lookup_commit_reference_gently(rev, 1);

	errs |= post_checkout_hook(head, head, 0);
	return errs;
}
