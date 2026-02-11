ocfs2_search_cache_tree(struct ocfs2_caching_info *ci,
			sector_t block)
{
	struct rb_node * n = ci->ci_cache.ci_tree.rb_node;
	struct ocfs2_meta_cache_item *item = NULL;

	while (n) {
		item = rb_entry(n, struct ocfs2_meta_cache_item, c_node);

		if (block < item->c_block)
			n = n->rb_left;
		else if (block > item->c_block)
			n = n->rb_right;
		else
			return item;
	}

	return NULL;
}
