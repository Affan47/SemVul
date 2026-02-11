dncache_flush(struct cache *cache)
{
    struct backdn *dn = NULL;

    if (!entryrdn_get_switch()) {
        return dn;
    }

    LOG("=> dncache_flush\n", 0, 0, 0);


    while ((cache->c_lrutail != NULL) && CACHE_FULL(cache)) {
        if (dn == NULL)
        {
            dn = CACHE_LRU_TAIL(cache, struct backdn *);
        }
        else
        {
            dn = BACK_LRU_PREV(dn, struct backdn *);
        }
        ASSERT(dn->ep_refcnt == 0);
        dn->ep_refcnt++;
        if (dncache_remove_int(cache, dn) < 0) {
           LDAPDebug(LDAP_DEBUG_ANY, "dn cache flush: unable to delete entry\n",
                    0, 0, 0);
           break;
        }
        if(dn == CACHE_LRU_HEAD(cache, struct backdn *)) {
            break;
        }
    }
    if (dn)
        LRU_DETACH(cache, dn);
    LOG("<= dncache_flush (down to %lu dns, %lu bytes)\n", cache->c_curentries,
        slapi_counter_get_value(cache->c_cursize), 0);
    return dn;
}
