cmd_diff_tree(int argc, const char **argv, const char *prefix)
{
	int nr_sha1;
	char line[1000];
	struct object *tree1, *tree2;
	static struct rev_info *opt = &log_tree_opt;
	int read_stdin = 0;

	init_revisions(opt, prefix);
	git_config(git_default_config);
	nr_sha1 = 0;
	opt->abbrev = 0;
	opt->diff = 1;
	argc = setup_revisions(argc, argv, opt, NULL);

	while (--argc > 0) {
		const char *arg = *++argv;

		if (!strcmp(arg, "--stdin")) {
			read_stdin = 1;
			continue;
		}
		usage(diff_tree_usage);
	}

	if (!opt->diffopt.output_format)
		opt->diffopt.output_format = DIFF_FORMAT_RAW;


	nr_sha1 = opt->pending.nr;
	switch (nr_sha1) {
	case 0:
		if (!read_stdin)
			usage(diff_tree_usage);
		break;
	case 1:
		tree1 = opt->pending.objects[0].item;
		diff_tree_commit_sha1(tree1->sha1);
		break;
	case 2:
		tree1 = opt->pending.objects[0].item;
		tree2 = opt->pending.objects[1].item;
		if (tree2->flags & UNINTERESTING) {
			struct object *tmp = tree2;
			tree2 = tree1;
			tree1 = tmp;
		}
		diff_tree_sha1(tree1->sha1,
			       tree2->sha1,
			       "", &opt->diffopt);
		log_tree_diff_flush(opt);
		break;
	}

	if (!read_stdin)
		return opt->diffopt.exit_with_status ?
		    opt->diffopt.has_changes: 0;

	if (opt->diffopt.detect_rename)
		opt->diffopt.setup |= (DIFF_SETUP_USE_SIZE_CACHE |
				       DIFF_SETUP_USE_CACHE);
	while (fgets(line, sizeof(line), stdin)) {
		unsigned char sha1[20];

		if (get_sha1_hex(line, sha1)) {
			fputs(line, stdout);
			fflush(stdout);
		}
		else
			diff_tree_stdin(line);
	}
	return opt->diffopt.exit_with_status ? opt->diffopt.has_changes: 0;
}
