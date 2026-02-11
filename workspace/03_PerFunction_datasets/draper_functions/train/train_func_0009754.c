cmd_merge_recursive(int argc, const char **argv, const char *prefix)
{
	static const char *bases[20];
	static unsigned bases_count = 0;
	int i, clean;
	const char *branch1, *branch2;
	struct commit *result, *h1, *h2;
	struct commit_list *ca = NULL;
	struct lock_file *lock = xcalloc(1, sizeof(struct lock_file));
	int index_fd;

	if (argv[0]) {
		int namelen = strlen(argv[0]);
		if (8 < namelen &&
		    !strcmp(argv[0] + namelen - 8, "-subtree"))
			subtree_merge = 1;
	}

	git_config(merge_config, NULL);
	if (getenv("GIT_MERGE_VERBOSITY"))
		verbosity = strtol(getenv("GIT_MERGE_VERBOSITY"), NULL, 10);

	if (argc < 4)
		die("Usage: %s <base>... -- <head> <remote> ...\n", argv[0]);

	for (i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "--"))
			break;
		if (bases_count < sizeof(bases)/sizeof(*bases))
			bases[bases_count++] = argv[i];
	}
	if (argc - i != 3)
		die("Not handling anything other than two heads merge.");
	if (verbosity >= 5)
		buffer_output = 0;

	branch1 = argv[++i];
	branch2 = argv[++i];

	h1 = get_ref(branch1);
	h2 = get_ref(branch2);

	branch1 = better_branch_name(branch1);
	branch2 = better_branch_name(branch2);

	if (show(3))
		printf("Merging %s with %s\n", branch1, branch2);

	index_fd = hold_locked_index(lock, 1);

	for (i = 0; i < bases_count; i++) {
		struct commit *ancestor = get_ref(bases[i]);
		ca = commit_list_insert(ancestor, &ca);
	}
	clean = merge_recursive(h1, h2, branch1, branch2, ca, &result);

	if (active_cache_changed &&
	    (write_cache(index_fd, active_cache, active_nr) ||
	     commit_locked_index(lock)))
			die ("unable to write %s", get_index_file());

	return clean ? 0: 1;
}
