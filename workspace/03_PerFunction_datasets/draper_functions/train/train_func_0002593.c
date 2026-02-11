hash_remove (HASH * table, void *key)
{
    HASHENT **he, *ptr;
    unsigned int sum;

    ASSERT (table != 0);
    ASSERT (key != 0);
    sum = table->hash_key (key) % table->numbuckets;
    for (he = &table->bucket[sum]; *he; he = &(*he)->next)
    {
	if (table->compare_key (key, (*he)->key) == 0)
	{
	    ptr = (*he)->next;
	    if (table->destroy)
		table->destroy ((*he)->data);
	    FREE (*he);
	    table->dbsize--;
	    *he = ptr;
	    return 0;
	}
    }
    return -1;
}
