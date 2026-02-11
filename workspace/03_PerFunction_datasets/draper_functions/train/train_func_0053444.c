Resize(HashTable *ht,size_t newsize)
{
    HashIndex hi,*hiptr;
    HashEntry **new_array;
    size_t new_max;
    char *p;

    if (ht == NULL)
        return CONTAINER_ERROR_BADARG;
    if (newsize == 0)
        new_max = ht->max * 2 + 1;
    else new_max = newsize;
    new_array = alloc_array(ht, new_max);
    for (hiptr = first(&hi); hiptr; hiptr = next(hiptr)) {
        size_t i = hiptr->This->hash % new_max;
        p = (char *)new_array;
        p += i * (ht->ElementSize+sizeof(HashEntry));
        hiptr->This->next = (HashEntry *)(p+sizeof(HashEntry)+ht->ElementSize);
        memcpy(p, hiptr->This,sizeof(HashEntry)+ht->ElementSize);
    }
    ht->array = new_array;
    ht->max = (unsigned)new_max;
    return 1;
}
