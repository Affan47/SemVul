get(const char *key)
{
	if (!key || !*key) return 0;

	return (gPicture *)g_hash_table_lookup(cache, (gconstpointer)key);
}
