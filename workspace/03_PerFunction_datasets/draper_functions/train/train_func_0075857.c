verify_uptodate_1(struct cache_entry *ce,
				   struct unpack_trees_options *o,
				   enum unpack_trees_error_types error_type)
{
	struct stat st;

	if (o->index_only || (!((ce->ce_flags & CE_VALID) || ce_skip_worktree(ce)) && (o->reset || ce_uptodate(ce))))
		return 0;

	if (!lstat(ce->name, &st)) {
		unsigned changed = ie_match_stat(o->src_index, ce, &st, CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE);
		if (!changed)
			return 0;


		if (S_ISGITLINK(ce->ce_mode))
			return 0;
		errno = 0;
	}
	if (errno == ENOENT)
		return 0;
	return o->gently ? -1 :
		add_rejected_path(o, error_type, ce->name);
}
