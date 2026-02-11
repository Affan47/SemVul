cmd_log_init(int argc, const char **argv, const char *prefix,
		      struct rev_info *rev)
{
	int i;
	int decorate = 0;

	rev->abbrev = DEFAULT_ABBREV;
	rev->commit_format = CMIT_FMT_DEFAULT;
	if (fmt_pretty)
		get_commit_format(fmt_pretty, rev);
	rev->verbose_header = 1;
	DIFF_OPT_SET(&rev->diffopt, RECURSIVE);
	rev->show_root_diff = default_show_root;
	rev->subject_prefix = fmt_patch_subject_prefix;

	if (default_date_mode)
		rev->date_mode = parse_date_format(default_date_mode);

	argc = setup_revisions(argc, argv, rev, "HEAD");

	if (rev->diffopt.pickaxe || rev->diffopt.filter)
		rev->always_show_header = 0;
	if (DIFF_OPT_TST(&rev->diffopt, FOLLOW_RENAMES)) {
		rev->always_show_header = 0;
		if (rev->diffopt.nr_paths != 1)
			usage("git logs can only follow renames on one pathname at a time");
	}
	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];
		if (!strcmp(arg, "--decorate")) {
			load_ref_decorations();
			decorate = 1;
		} else
			die("unrecognized argument: %s", arg);
	}
	DIFF_OPT_SET(&rev->diffopt, ALLOW_TEXTCONV);
}
