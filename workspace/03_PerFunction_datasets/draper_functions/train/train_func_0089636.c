invalidate()
{
	char *key;
	void *value;

	if (dircache_table) {
		hash_table_firstkey(dircache_table);
		while (hash_table_nextkey(dircache_table, &key, &value)) {
			hash_table_remove(dircache_table, key);
			free(value);
		}
	}

	if (dircache_path) {
		free(dircache_path);
		dircache_path = 0;
	}
}
