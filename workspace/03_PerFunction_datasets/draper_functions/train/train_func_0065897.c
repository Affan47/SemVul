hevset_insert_key(hevset_t *ht, const void *key)
{
	hevset_check(ht);
	g_assert(key != NULL);

	hash_insert_key(HASH(ht), key);
	ht->stamp++;
}
