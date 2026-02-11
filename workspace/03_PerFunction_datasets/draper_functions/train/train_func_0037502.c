hash_lookup (HASH * table, void *key)
{
    HASHENT *he;
    unsigned int sum;

    if (!table)
	return 0;
    ASSERT (key != 0);
    sum = table->hash_key (key) % table->numbuckets;
    he = table->bucket[sum];

    for (; he; he = he->next)
    {
	if (table->compare_key (key, he->key) == 0)
	    return he->data;
    }
    return 0;
}
