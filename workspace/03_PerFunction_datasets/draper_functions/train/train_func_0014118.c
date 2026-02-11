InitCRLCache(void)
{
    if (PR_FALSE == crlcache_initialized)
    {
        PORT_Assert(NULL == crlcache.lock);
        PORT_Assert(NULL == crlcache.issuers);
        PORT_Assert(NULL == namedCRLCache.lock);
        PORT_Assert(NULL == namedCRLCache.entries);
        if (crlcache.lock || crlcache.issuers || namedCRLCache.lock ||
            namedCRLCache.entries)
        {

            PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
            return SECFailure;
        }
#ifdef GLOBAL_RWLOCK
        crlcache.lock = NSSRWLock_New(NSS_RWLOCK_RANK_NONE, NULL);
#else
        crlcache.lock = PR_NewLock();
#endif
        namedCRLCache.lock = PR_NewLock();
        crlcache.issuers = PL_NewHashTable(0, SECITEM_Hash, SECITEM_HashCompare,
                                  PL_CompareValues, NULL, NULL);
        namedCRLCache.entries = PL_NewHashTable(0, SECITEM_Hash, SECITEM_HashCompare,
                                  PL_CompareValues, NULL, NULL);
        if (!crlcache.lock || !namedCRLCache.lock || !crlcache.issuers ||
            !namedCRLCache.entries)
        {
            if (crlcache.lock)
            {
#ifdef GLOBAL_RWLOCK
                NSSRWLock_Destroy(crlcache.lock);
#else
                PR_DestroyLock(crlcache.lock);
#endif
                crlcache.lock = NULL;
            }
            if (namedCRLCache.lock)
            {
                PR_DestroyLock(namedCRLCache.lock);
                namedCRLCache.lock = NULL;
            }
            if (crlcache.issuers)
            {
                PL_HashTableDestroy(crlcache.issuers);
                crlcache.issuers = NULL;
            }
            if (namedCRLCache.entries)
            {
                PL_HashTableDestroy(namedCRLCache.entries);
                namedCRLCache.entries = NULL;
            }

            return SECFailure;
        }
        crlcache_initialized = PR_TRUE;
        return SECSuccess;
    }
    else
    {
        PORT_Assert(crlcache.lock);
        PORT_Assert(crlcache.issuers);
        if ( (NULL == crlcache.lock) || (NULL == crlcache.issuers) )
        {

            return SECFailure;
        }
        else
        {

            return SECSuccess;
        }
    }
}
