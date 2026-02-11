HashFind(HashTablePtr table,
			      unsigned long key, unsigned long *h)
{
    unsigned long hash = HashHash(key);
    HashBucketPtr prev = NULL;
    HashBucketPtr bucket;

    if (h) *h = hash;

    for (bucket = table->buckets[hash]; bucket; bucket = bucket->next) {
	if (bucket->key == key) {
	    if (prev) {

		prev->next           = bucket->next;
		bucket->next         = table->buckets[hash];
		table->buckets[hash] = bucket;
		++table->partials;
	    } else {
		++table->hits;
	    }
	    return bucket;
	}
	prev = bucket;
    }
    ++table->misses;
    return NULL;
}
