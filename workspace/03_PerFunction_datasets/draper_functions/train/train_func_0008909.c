deleted_entry(struct cache_entry *ce, struct cache_entry *old,
		struct unpack_trees_options *o)
{

	if (!old) {
		if (verify_absent(ce, "removed", o))
			return -1;
		return 0;
	}
	if (verify_uptodate(old, o))
		return -1;
	add_entry(o, ce, CE_REMOVE, 0);
	invalidate_ce_path(ce, o);
	return 1;
}
