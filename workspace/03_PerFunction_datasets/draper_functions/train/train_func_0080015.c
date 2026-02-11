cmd_rev_list(int argc, const char **argv, const char *prefix)
{
	struct commit_list *list;
	int i;
	int read_from_stdin = 0;
	int bisect_show_vars = 0;

	git_config(git_default_config);
	init_revisions(&revs, prefix);
	revs.abbrev = 0;
	revs.commit_format = CMIT_FMT_UNSPECIFIED;
	argc = setup_revisions(argc, argv, &revs, NULL);

	for (i = 1 ; i < argc; i++) {
		const char *arg = argv[i];

		if (!strcmp(arg, "--header")) {
			revs.verbose_header = 1;
			continue;
		}
		if (!strcmp(arg, "--timestamp")) {
			show_timestamp = 1;
			continue;
		}
		if (!strcmp(arg, "--bisect")) {
			bisect_list = 1;
			continue;
		}
		if (!strcmp(arg, "--bisect-vars")) {
			bisect_list = 1;
			bisect_show_vars = 1;
			continue;
		}
		if (!strcmp(arg, "--stdin")) {
			if (read_from_stdin++)
				die("--stdin given twice?");
			read_revisions_from_stdin(&revs);
			continue;
		}
		usage(rev_list_usage);

	}
	if (revs.commit_format != CMIT_FMT_UNSPECIFIED) {

		hdr_termination = '\n';
		if (revs.commit_format == CMIT_FMT_ONELINE)
			header_prefix = "";
		else
			header_prefix = "commit ";
	}
	else if (revs.verbose_header)

		revs.commit_format = CMIT_FMT_RAW;

	list = revs.commits;

	if ((!list &&
	     (!(revs.tag_objects||revs.tree_objects||revs.blob_objects) &&
	      !revs.pending.nr)) ||
	    revs.diff)
		usage(rev_list_usage);

	save_commit_buffer = revs.verbose_header || revs.grep_filter;
	track_object_refs = 0;
	if (bisect_list)
		revs.limited = 1;

	prepare_revision_walk(&revs);
	if (revs.tree_objects)
		mark_edges_uninteresting(revs.commits, &revs, show_edge);

	if (bisect_list) {
		int reaches = reaches, all = all;

		revs.commits = find_bisection(revs.commits, &reaches, &all);
		if (bisect_show_vars) {
			int cnt;
			if (!revs.commits)
				return 1;


			cnt = all-reaches;
			if (cnt < reaches)
				cnt = reaches;
			printf("bisect_rev=%s\n"
			       "bisect_nr=%d\n"
			       "bisect_good=%d\n"
			       "bisect_bad=%d\n"
			       "bisect_all=%d\n",
			       sha1_to_hex(revs.commits->item->object.sha1),
			       cnt - 1,
			       all - reaches - 1,
			       reaches - 1,
			       all);
			return 0;
		}
	}

	traverse_commit_list(&revs, show_commit, show_object);

	return 0;
}
