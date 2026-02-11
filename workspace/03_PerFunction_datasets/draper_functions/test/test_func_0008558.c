gfarm_hash_table_free(struct gfarm_hash_table *hashtab)
{
	int i;
	struct gfarm_hash_entry *p, *np;

	for (i = 0; i < hashtab->table_size; i++) {
		for (p = hashtab->buckets[i]; p != NULL; p = np) {
			np = p->next;
			free(p);
		}
	}
	free(hashtab);
}
