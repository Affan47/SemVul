commit_match(struct commit *commit, struct rev_info *opt)
{
	if (!opt->grep_filter.pattern_list && !opt->grep_filter.header_list)
		return 1;
	return grep_buffer(&opt->grep_filter,
			   NULL,
			   commit->buffer, strlen(commit->buffer));
}
