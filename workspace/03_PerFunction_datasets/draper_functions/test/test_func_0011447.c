verify_uptodate_1(struct cache_entry *ce,
				   struct unpack_trees_options *o,
				   const char *error_msg)
{
	struct stat st;

	if (o->index_only || (!ce_skip_worktree(ce) && (o->reset || ce_uptodate(ce))))
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
		error(error_msg, ce->name);
}
