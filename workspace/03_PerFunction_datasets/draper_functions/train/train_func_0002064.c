ohash_key_hash(const void *key)
{
	const struct ohash_pair *op = key;

	g_assert(key != NULL);
	ohash_table_check(op->oh);

	return (*op->oh->hash_func)(op->key);
}
