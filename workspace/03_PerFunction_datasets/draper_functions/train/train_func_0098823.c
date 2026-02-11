release_hash_table(struct hashtable * ht){
	int i;

	if (ht == NULL) return;
	for (i = 0; i < ht->tablesize; i++)
 		if (ht->table[i])
 			destroy_password(ht->table[i]);
	if (ht->table) {
		free(ht->table);
		ht->table = NULL;
	}
	if (ht->fp) {
		fclose(ht->fp);
		ht->fp = NULL;
	}
	ht->tablesize = 0;
}
