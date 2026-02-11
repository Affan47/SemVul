verify_uptodate(struct cache_entry *ce,
		struct unpack_trees_options *o)
{
	struct stat st;

	if (o->index_only || o->reset)
		return;

	if (!lstat(ce->name, &st)) {
		unsigned changed = ce_match_stat(ce, &st, 1);
		if (!changed)
			return;
		errno = 0;
	}
	if (errno == ENOENT)
		return;
	die("Entry '%s' not uptodate. Cannot merge.", ce->name);
}
