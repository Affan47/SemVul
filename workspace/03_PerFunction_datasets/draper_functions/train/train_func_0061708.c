bch_btree_insert_keys(struct btree *b, struct btree_op *op,
				  struct keylist *insert_keys,
				  struct bkey *replace_key)
{
	bool ret = false;
	int oldsize = bch_count_data(&b->keys);

	while (!bch_keylist_empty(insert_keys)) {
		struct bkey *k = insert_keys->keys;

		if (bkey_u64s(k) > insert_u64s_remaining(b))
			break;

		if (bkey_cmp(k, &b->key) <= 0) {
			if (!b->level)
				bkey_put(b->c, k);

			ret |= btree_insert_key(b, k, replace_key);
			bch_keylist_pop_front(insert_keys);
		} else if (bkey_cmp(&START_KEY(k), &b->key) < 0) {
			BKEY_PADDED(key) temp;
			bkey_copy(&temp.key, insert_keys->keys);

			bch_cut_back(&b->key, &temp.key);
			bch_cut_front(&b->key, insert_keys->keys);

			ret |= btree_insert_key(b, &temp.key, replace_key);
			break;
		} else {
			break;
		}
	}

	if (!ret)
		op->insert_collision = true;

	BUG_ON(!bch_keylist_empty(insert_keys) && b->level);

	BUG_ON(bch_count_data(&b->keys) < oldsize);
	return ret;
}
