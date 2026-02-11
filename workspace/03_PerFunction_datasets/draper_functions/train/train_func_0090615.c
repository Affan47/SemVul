nls_hash_term(nls_hash *hash)
{
	int i;
	nls_hash_entry *table = hash->nh_table;

	for (i = 0; i < NLS_HASH_WIDTH; i++) {
		if (table[i].nhe_next) {
			nls_release(table[i].nhe_next);
		}
		table[i].nhe_next = NULL;
	}
	hash->nh_num = 0;
}
