git_diff_find_init_options(
	git_diff_find_options *opts, unsigned int version)
{
	GIT_INIT_STRUCTURE_FROM_TEMPLATE(
		opts, version, git_diff_find_options, GIT_DIFF_FIND_OPTIONS_INIT);
	return 0;
}
