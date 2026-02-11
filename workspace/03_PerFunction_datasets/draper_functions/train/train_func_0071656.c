mca_cannibalize(struct cache_set *c, struct btree_op *op,
				     struct bkey *k)
{
	struct btree *b;

	trace_bcache_btree_cache_cannibalize(c);

	if (mca_cannibalize_lock(c, op))
		return ERR_PTR(-EINTR);

	list_for_each_entry_reverse(b, &c->btree_cache, list)
		if (!mca_reap(b, btree_order(k), false))
			return b;

	list_for_each_entry_reverse(b, &c->btree_cache, list)
		if (!mca_reap(b, btree_order(k), true))
			return b;

	WARN(1, "btree cache cannibalize failed\n");
	return ERR_PTR(-ENOMEM);
}
