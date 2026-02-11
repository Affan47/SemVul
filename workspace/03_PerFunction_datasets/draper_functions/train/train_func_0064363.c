show_bisect_vars(struct rev_list_info *info, int reaches, int all)
{
	int cnt, flags = info->bisect_show_flags;
	char hex[41] = "";
	struct commit_list *tried;
	struct rev_info *revs = info->revs;

	if (!revs->commits && !(flags & BISECT_SHOW_TRIED))
		return 1;

	revs->commits = filter_skipped(revs->commits, &tried,
				       flags & BISECT_SHOW_ALL,
				       NULL, NULL);


	cnt = all - reaches;
	if (cnt < reaches)
		cnt = reaches;

	if (revs->commits)
		strcpy(hex, sha1_to_hex(revs->commits->item->object.sha1));

	if (flags & BISECT_SHOW_ALL) {
		traverse_commit_list(revs, show_commit, show_object, info);
		printf("------\n");
	}

	if (flags & BISECT_SHOW_TRIED)
		show_tried_revs(tried);

	print_var_str("bisect_rev", hex);
	print_var_int("bisect_nr", cnt - 1);
	print_var_int("bisect_good", all - reaches - 1);
	print_var_int("bisect_bad", reaches - 1);
	print_var_int("bisect_all", all);
	print_var_int("bisect_steps", estimate_bisect_steps(all));

	return 0;
}
