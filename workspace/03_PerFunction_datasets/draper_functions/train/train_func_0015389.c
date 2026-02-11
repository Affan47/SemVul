hash_del(struct hash *hash, const char *key)
{
	unsigned int keylen = strlen(key);
	unsigned int hashval = hash_superfast(key, keylen);
	unsigned int pos = hashval % hash->n_buckets;
	unsigned int steps_used, steps_total;
	struct hash_bucket *bucket = hash->buckets + pos;
	struct hash_entry *entry, *entry_end;
	const struct hash_entry se = {
		.key = key,
		.value = NULL
	};

	entry = bsearch(&se, bucket->entries, bucket->used,
		sizeof(struct hash_entry), hash_entry_cmp);
	if (entry == NULL)
		return -ENOENT;

	entry_end = bucket->entries + bucket->used;
	memmove(entry, entry + 1,
		(entry_end - entry) * sizeof(struct hash_entry));

	bucket->used--;
	hash->count--;

	steps_used = bucket->used / hash->step;
	steps_total = bucket->total / hash->step;
	if (steps_used + 1 < steps_total) {
		size_t size = (steps_used + 1) *
			hash->step * sizeof(struct hash_entry);
		struct hash_entry *tmp = realloc(bucket->entries, size);
		if (tmp) {
			bucket->entries = tmp;
			bucket->total = (steps_used + 1) * hash->step;
		}
	}

	return 0;
}
