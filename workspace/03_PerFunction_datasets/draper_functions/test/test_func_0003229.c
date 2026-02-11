hash_table_clear(struct hash_table *h)
{
	struct entry *e, *f;
	int i;

	for(i = 0; i < h->bucket_count; i++) {
		e = h->buckets[i];
		while(e) {
			f = e->next;
			free(e->key);
			free(e);
			e = f;
		}
	}

	for(i = 0; i < h->bucket_count; i++) {
		h->buckets[i] = 0;
	}
}
