do_oneway_diff(struct unpack_trees_options *o,
	struct cache_entry *idx,
	struct cache_entry *tree)
{
	struct rev_info *revs = o->unpack_data;
	int match_missing, cached;


	cached = o->index_only ||
		(idx && ((idx->ce_flags & CE_VALID) || ce_skip_worktree(idx)));


	match_missing = !revs->ignore_merges;

	if (cached && idx && ce_stage(idx)) {
		struct diff_filepair *pair;
		pair = diff_unmerge(&revs->diffopt, idx->name);
		fill_filespec(pair->one, idx->sha1, idx->ce_mode);
		return;
	}


	if (!tree) {
		show_new_file(revs, idx, cached, match_missing);
		return;
	}


	if (!idx) {
		diff_index_show_file(revs, "-", tree, tree->sha1, tree->ce_mode, 0);
		return;
	}


	show_modified(revs, tree, idx, 1, cached, match_missing);
}
