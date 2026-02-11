unref(CollData *collData)
{
    CollDataCacheEntry *entry = NULL;

    umtx_lock(&lock);
    entry = (CollDataCacheEntry *) uhash_get(cache, collData->key);

    if (entry != NULL) {
        entry->refCount -= 1;
    }
    umtx_unlock(&lock);
}
