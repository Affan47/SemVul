write_tree_from_memory(struct merge_options *o)
{
	struct tree *result = NULL;

	if (unmerged_cache()) {
		int i;
		output(o, 0, "There are unmerged index entries:");
		for (i = 0; i < active_nr; i++) {
			struct cache_entry *ce = active_cache[i];
			if (ce_stage(ce))
				output(o, 0, "%d %.*s", ce_stage(ce), ce_namelen(ce), ce->name);
		}
		return NULL;
	}

	if (!active_cache_tree)
		active_cache_tree = cache_tree();

	if (!cache_tree_fully_valid(active_cache_tree) &&
	    cache_tree_update(active_cache_tree,
			      active_cache, active_nr, 0, 0) < 0)
		die("error building trees");

	result = lookup_tree(active_cache_tree->sha1);

	return result;
}
