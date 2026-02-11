ocsp_CreateOrUpdateCacheEntry(OCSPCacheData *cache,
                              CERTOCSPCertID *certID,
                              CERTOCSPSingleResponse *single,
                              PRBool *certIDWasConsumed)
{
    SECStatus rv;
    OCSPCacheItem *cacheItem;
    OCSP_TRACE(("OCSP ocsp_CreateOrUpdateCacheEntry\n"));

    if (certIDWasConsumed)
        *certIDWasConsumed = PR_FALSE;

    PR_EnterMonitor(OCSP_Global.monitor);
    PORT_Assert(OCSP_Global.maxCacheEntries >= 0);

    cacheItem = ocsp_FindCacheEntry(cache, certID);


    if (!single && cacheItem && cacheItem->certStatusArena &&
        (cacheItem->certStatus.certStatusType == ocspCertStatus_revoked ||
         cacheItem->certStatus.certStatusType == ocspCertStatus_unknown)) {
        PR_ExitMonitor(OCSP_Global.monitor);
        return SECSuccess;
    }

    if (!cacheItem) {
        CERTOCSPCertID *myCertID;
        if (certIDWasConsumed) {
            myCertID = certID;
            *certIDWasConsumed = PR_TRUE;
        } else {
            myCertID = cert_DupOCSPCertID(certID);
            if (!myCertID) {
                PR_ExitMonitor(OCSP_Global.monitor);
                PORT_SetError(PR_OUT_OF_MEMORY_ERROR);
                return SECFailure;
            }
        }

        rv = ocsp_CreateCacheItemAndConsumeCertID(cache, myCertID,
                                                  &cacheItem);
        if (rv != SECSuccess) {
            PR_ExitMonitor(OCSP_Global.monitor);
            return rv;
        }
    }
    if (single) {
        PRTime thisUpdate;
        rv = DER_GeneralizedTimeToTime(&thisUpdate, &single->thisUpdate);

        if (!cacheItem->haveThisUpdate ||
            (rv == SECSuccess && cacheItem->thisUpdate < thisUpdate)) {
            rv = ocsp_SetCacheItemResponse(cacheItem, single);
            if (rv != SECSuccess) {
                ocsp_RemoveCacheItem(cache, cacheItem);
                PR_ExitMonitor(OCSP_Global.monitor);
                return rv;
            }
        } else {
            OCSP_TRACE(("Not caching response because the response is not "
                        "newer than the cache"));
        }
    } else {
        cacheItem->missingResponseError = PORT_GetError();
        if (cacheItem->certStatusArena) {
            PORT_FreeArena(cacheItem->certStatusArena, PR_FALSE);
            cacheItem->certStatusArena = NULL;
        }
    }
    ocsp_FreshenCacheItemNextFetchAttemptTime(cacheItem);
    ocsp_CheckCacheSize(cache);

    PR_ExitMonitor(OCSP_Global.monitor);
    return SECSuccess;
}
