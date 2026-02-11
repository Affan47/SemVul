Clear(HashTable *ht)
{
    HashIndex HashIdx,*hi;
    for (hi = first(&HashIdx); hi; hi = next(hi))
        HashSet(ht, hi->This->key, hi->This->klen, NULL);
    return 1;
}
