htable_delete(htable ht)
{
	hbucket bucket, next;
	unsigned int i;

	for (i = 0; i < ht->size; i++) {
		bucket = ht->table[i];
		while (bucket != NULL) {
			next = bucket->next;
			free_bucket(bucket);
			bucket = next;
		}
	}

	free(ht->table);
	free(ht);
}
