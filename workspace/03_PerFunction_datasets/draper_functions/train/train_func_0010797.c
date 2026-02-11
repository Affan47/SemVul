netsnmp_cache_remove(netsnmp_cache *cache)
{
    netsnmp_cache  *cur,*prev;

    if (!cache || !cache_head)
        return -1;

    if (cache == cache_head) {
        cache_head = cache_head->next;
        if (cache_head)
            cache_head->prev = NULL;
        return 0;
    }

    prev = cache_head;
    cur = cache_head->next;
    for (; cur; prev = cur, cur = cur->next) {
        if (cache == cur) {
            prev->next = cur->next;
            if (cur->next)
                cur->next->prev = cur->prev;
            return 0;
        }
    }
    return -1;
}
