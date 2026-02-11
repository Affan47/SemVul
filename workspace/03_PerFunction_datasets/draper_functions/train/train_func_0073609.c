hash_table_foreach(const hash_table_t *ht, ckeyval_fn_t func, void *data)
{
	size_t i, n;

	hash_table_check(ht);
	g_assert(func != NULL);

	ht_synchronize(ht);

	n = ht->num_held;
	i = ht->num_bins;

	while (i-- > 0) {
		hash_item_t *item;

		for (item = ht->bins[i]; NULL != item; item = item->next) {
			(*func)(item->key, deconstify_pointer(item->value), data);
			n--;
		}
	}
	g_assert(0 == n);

	ht_return_void(ht);
}
