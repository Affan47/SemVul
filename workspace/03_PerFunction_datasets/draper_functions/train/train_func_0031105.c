gfarm_hash_iterator_valid_entry(struct gfarm_hash_iterator *iterator)
{
	struct gfarm_hash_table *hashtab = iterator->table;

	if (iterator->bucket_index >= hashtab->table_size)
		return (0);
	while (*iterator->pp == NULL) {
		if (++iterator->bucket_index >= hashtab->table_size)
			return (0);
		iterator->pp = &hashtab->buckets[iterator->bucket_index];
	}
	return (1);
}
