merged_entry(struct cache_entry *merge, struct cache_entry *old,
		struct unpack_trees_options *o)
{
	int update = CE_UPDATE;

	if (!old) {
		if (verify_absent(merge, ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN, o))
			return -1;
		if (!o->skip_sparse_checkout && will_have_skip_worktree(merge, o))
			update |= CE_SKIP_WORKTREE;
		invalidate_ce_path(merge, o);
	} else if (!(old->ce_flags & CE_CONFLICTED)) {


		if (same(old, merge)) {
			copy_cache_entry(merge, old);
			update = 0;
		} else {
			if (verify_uptodate(old, o))
				return -1;
			if (ce_skip_worktree(old))
				update |= CE_SKIP_WORKTREE;
			invalidate_ce_path(old, o);
		}
	} else {


		invalidate_ce_path(old, o);
	}

	add_entry(o, merge, update, CE_STAGEMASK);
	return 1;
}
