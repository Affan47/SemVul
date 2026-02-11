drmHashLookup(void *t, unsigned long key, void **value)
{
    HashTablePtr  table = (HashTablePtr)t;
    HashBucketPtr bucket;

    if (!table || table->magic != HASH_MAGIC) return -1;

    bucket = HashFind(table, key, NULL);
    if (!bucket) return 1;
    *value = bucket->value;
    return 0;
}
