expando_find_long(const char *key)
{
	EXPANDO_REC *rec = g_hash_table_lookup(expandos, key);
	return rec == NULL ? NULL : rec->func;
}
