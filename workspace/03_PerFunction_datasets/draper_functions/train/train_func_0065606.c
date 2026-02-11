log_tree_diff(struct rev_info *opt, struct commit *commit, struct log_info *log)
{
	int showed_log;
	struct commit_list *parents;
	unsigned const char *sha1 = commit->object.sha1;

	if (!opt->diff)
		return 0;


	parents = commit->parents;
	if (!parents) {
		if (opt->show_root_diff) {
			diff_root_tree_sha1(sha1, "", &opt->diffopt);
			log_tree_diff_flush(opt);
		}
		return !opt->loginfo;
	}


	if (parents && parents->next) {
		if (opt->ignore_merges)
			return 0;
		else if (opt->combine_merges)
			return do_diff_combined(opt, commit);


		log->parent = parents->item;
	}

	showed_log = 0;
	for (;;) {
		struct commit *parent = parents->item;

		diff_tree_sha1(parent->object.sha1, sha1, "", &opt->diffopt);
		log_tree_diff_flush(opt);

		showed_log |= !opt->loginfo;


		parents = parents->next;
		if (!parents)
			break;
		log->parent = parents->item;
		opt->loginfo = log;
	}
	return showed_log;
}
