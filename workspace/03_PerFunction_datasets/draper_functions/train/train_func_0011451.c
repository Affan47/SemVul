apply_sparse_checkout(struct cache_entry *ce, struct unpack_trees_options *o)
{
	int was_skip_worktree = ce_skip_worktree(ce);

	if (ce->ce_flags & CE_NEW_SKIP_WORKTREE)
		ce->ce_flags |= CE_SKIP_WORKTREE;
	else
		ce->ce_flags &= ~CE_SKIP_WORKTREE;


	if (was_skip_worktree && ce_skip_worktree(ce)) {
		ce->ce_flags &= ~CE_UPDATE;


		if (ce->ce_flags & CE_REMOVE)
			ce->ce_flags &= ~CE_WT_REMOVE;
	}

	if (!was_skip_worktree && ce_skip_worktree(ce)) {


		if (!(ce->ce_flags & CE_UPDATE) && verify_uptodate_sparse(ce, o))
			return -1;
		ce->ce_flags |= CE_WT_REMOVE;
	}
	if (was_skip_worktree && !ce_skip_worktree(ce)) {
		if (verify_absent_sparse(ce, ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN, o))
			return -1;
		ce->ce_flags |= CE_UPDATE;
	}
	return 0;
}
