make_btree_freeing_key(struct btree *b, struct bkey *k)
{
	unsigned i;

	mutex_lock(&b->c->bucket_lock);

	atomic_inc(&b->c->prio_blocked);

	bkey_copy(k, &b->key);
	bkey_copy_key(k, &ZERO_KEY);

	for (i = 0; i < KEY_PTRS(k); i++)
		SET_PTR_GEN(k, i,
			    bch_inc_gen(PTR_CACHE(b->c, &b->key, i),
					PTR_BUCKET(b->c, &b->key, i)));

	mutex_unlock(&b->c->bucket_lock);
}
