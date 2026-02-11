ShutdownCRLCache(void)
{
    SECStatus rv = SECSuccess;
    if (PR_FALSE == crlcache_initialized &&
        !crlcache.lock && !crlcache.issuers)
    {

        return SECSuccess;
    }
    if (PR_TRUE == crlcache_initialized &&
        (!crlcache.lock || !crlcache.issuers || !namedCRLCache.lock ||
         !namedCRLCache.entries))
    {

        PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
        return SECFailure;
    }


    PL_HashTableEnumerateEntries(crlcache.issuers, &FreeIssuer, &rv);

    PL_HashTableDestroy(crlcache.issuers);
    crlcache.issuers = NULL;

#ifdef GLOBAL_RWLOCK
    NSSRWLock_Destroy(crlcache.lock);
#else
    PR_DestroyLock(crlcache.lock);
#endif
    crlcache.lock = NULL;


    PL_HashTableEnumerateEntries(namedCRLCache.entries, &FreeNamedEntries, &rv);

    PL_HashTableDestroy(namedCRLCache.entries);
    namedCRLCache.entries = NULL;

    PR_DestroyLock(namedCRLCache.lock);
    namedCRLCache.lock = NULL;

    crlcache_initialized = PR_FALSE;
    return rv;
}
