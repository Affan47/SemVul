hash_lookup(hash_t *hash, const void *key)
{
    hash_val_t hkey, chain;
    hnode_t *nptr;

    hkey = hash->function(key);
    chain = hkey & hash->mask;

    for (nptr = hash->table[chain]; nptr; nptr = nptr->next) {
	if (nptr->hkey == hkey && hash->compare(nptr->key, key) == 0)
	    return nptr;
    }

    return NULL;
}
