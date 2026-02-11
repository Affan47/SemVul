FindSID(cacheDesc *cache, PRUint32 setNum, PRUint32 now,
        const PRIPv6Addr *addr, unsigned char *sessionID,
	unsigned sessionIDLength)
{
    PRUint32      ndx   = cache->sidCacheSets[setNum].next;
    int           i;

    sidCacheEntry * set = cache->sidCacheData +
    			 (setNum * SID_CACHE_ENTRIES_PER_SET);

    for (i = SID_CACHE_ENTRIES_PER_SET; i > 0; --i) {
	sidCacheEntry * sce;

	ndx  = (ndx - 1) % SID_CACHE_ENTRIES_PER_SET;
	sce = set + ndx;

	if (!sce->valid)
	    continue;

	if (now > sce->expirationTime) {

	    SSL_TRC(7, ("%d: timed out sid entry addr=%08x%08x%08x%08x now=%x "
			"time+=%x",
			myPid, sce->addr.pr_s6_addr32[0],
			sce->addr.pr_s6_addr32[1], sce->addr.pr_s6_addr32[2],
			sce->addr.pr_s6_addr32[3], now,
			sce->expirationTime ));
	    sce->valid = 0;
	    continue;
	}


	if (sessionIDLength == sce->sessionIDLength      &&
	    !memcmp(&sce->addr, addr, sizeof(PRIPv6Addr)) &&
	    !memcmp(sce->sessionID, sessionID, sessionIDLength)) {

	    return sce;
	}
    }

    PORT_SetError(SSL_ERROR_SESSION_NOT_FOUND);
    return NULL;
}
