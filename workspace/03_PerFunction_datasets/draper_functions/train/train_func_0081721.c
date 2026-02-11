fr_hash_table_find(fr_hash_table_t *ht,
					       const void *data)
{
	uint32_t key;
	uint32_t entry;
	uint32_t reversed;

	if (!ht) return NULL;

	key = ht->hash(data);
	entry = key & ht->mask;
	reversed = reverse(key);

	if (!ht->buckets[entry]) fr_hash_table_fixup(ht, entry);

	return list_find(ht, ht->buckets[entry], reversed, data);
}
