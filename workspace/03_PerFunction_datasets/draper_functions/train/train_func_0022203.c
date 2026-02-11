show_diff_tree(const char *prefix, struct commit *commit)
{
	struct rev_info opt;


	init_revisions(&opt, prefix);
	git_config(git_diff_basic_config, NULL);
	opt.abbrev = 0;
	opt.diff = 1;


	opt.verbose_header = 1;
	opt.use_terminator = 0;
	opt.commit_format = CMIT_FMT_DEFAULT;


	if (!opt.diffopt.output_format)
		opt.diffopt.output_format = DIFF_FORMAT_RAW;

	log_tree_commit(&opt, commit);
}
