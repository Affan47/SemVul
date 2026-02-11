hash_list_find(hash_list_t *hl, const void *key,
	const void **orig_key_ptr)
{
	struct hash_list_item *item;

	hash_list_check(hl);

	item = hikset_lookup(hl->ht, key);
	if (item && orig_key_ptr) {
		*orig_key_ptr = item->key;
	}
	return NULL != item;
}
