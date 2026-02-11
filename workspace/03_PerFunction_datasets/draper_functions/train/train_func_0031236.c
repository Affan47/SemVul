hash_table_new(hash_func_t hash_func, compare_func_t compare_func)
{
	hashtable_t* ht = (hashtable_t*)malloc(sizeof(hashtable_t));
	int i;
	for (i = 0; i < 256; i++) {
		ht->entries[i] = NULL;
	}
	ht->count = 0;
	ht->hash_func = hash_func;
	ht->compare_func = compare_func;
	return ht;
}
