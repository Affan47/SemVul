builtin_diff_index(struct rev_info *revs,
			      int argc, const char **argv)
{
	int cached = 0;
	while (1 < argc) {
		const char *arg = argv[1];
		if (!strcmp(arg, "--cached"))
			cached = 1;
		else
			usage(builtin_diff_usage);
		argv++; argc--;
	}


	if (revs->pending.nr != 1 ||
	    revs->max_count != -1 || revs->min_age != -1 ||
	    revs->max_age != -1)
		usage(builtin_diff_usage);
	if (read_cache() < 0) {
		perror("read_cache");
		return -1;
	}
	return run_diff_index(revs, cached);
}
