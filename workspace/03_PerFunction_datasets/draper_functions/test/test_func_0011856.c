host_hashtab_lookup(struct gfarm_hash_table *hashtab, const char *hostname)
{
	struct gfarm_hash_entry *entry;

	entry = gfarm_hash_lookup(hashtab, &hostname, sizeof(hostname));
	if (entry == NULL)
		return (NULL);
	return (*(struct host **)gfarm_hash_entry_data(entry));
}
