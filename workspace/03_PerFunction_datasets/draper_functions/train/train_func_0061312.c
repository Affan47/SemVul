bch_extent_bad(struct btree_keys *bk, const struct bkey *k)
{
	struct btree *b = container_of(bk, struct btree, keys);
	struct bucket *g;
	unsigned i, stale;

	if (!KEY_PTRS(k) ||
	    bch_extent_invalid(bk, k))
		return true;

	for (i = 0; i < KEY_PTRS(k); i++)
		if (!ptr_available(b->c, k, i))
			return true;

	if (!expensive_debug_checks(b->c) && KEY_DIRTY(k))
		return false;

	for (i = 0; i < KEY_PTRS(k); i++) {
		g = PTR_BUCKET(b->c, k, i);
		stale = ptr_stale(b->c, k, i);

		btree_bug_on(stale > 96, b,
			     "key too stale: %i, need_gc %u",
			     stale, b->c->need_gc);

		btree_bug_on(stale && KEY_DIRTY(k) && KEY_SIZE(k),
			     b, "stale dirty pointer");

		if (stale)
			return true;

		if (expensive_debug_checks(b->c) &&
		    bch_extent_bad_expensive(b, k, i))
			return true;
	}

	return false;
}
