cache_remove(struct cache *cache,  void *ptr)
{
    int ret = 0;
    struct backcommon *e;
    if (NULL == ptr)
    {
        LOG("=> lru_remove\n<= lru_remove (null entry)\n", 0, 0, 0);
        return ret;
    }
    e = (struct backcommon *)ptr;

    PR_Lock(cache->c_mutex);
    if (CACHE_TYPE_ENTRY == e->ep_type) {
        ASSERT(e->ep_refcnt > 0);
        ret = entrycache_remove_int(cache, (struct backentry *)e);
    } else if (CACHE_TYPE_DN == e->ep_type) {
        ret = dncache_remove_int(cache, (struct backdn *)e);
    }
    PR_Unlock(cache->c_mutex);
    return ret;
}
