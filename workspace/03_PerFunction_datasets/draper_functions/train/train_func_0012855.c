Cache_destroy(Cache *cache)
{
    int i = 0;
    check(cache, "NULL cache argument to Cache_destroy");

    if(cache->evict) {
        for(i = 0; i < cache->size; i++) {
            if(cache->arr[i].data) {
                cache->evict(cache->arr[i].data);
            }
        }
    }

    free(cache);

error:
    return;
}
