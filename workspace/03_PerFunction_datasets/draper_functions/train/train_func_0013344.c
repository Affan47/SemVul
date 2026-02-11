DPCache_FetchFromTokens(CRLDPCache* cache, PRTime vfdate,
                                         void* wincx)
{
    SECStatus rv = SECSuccess;
    CERTCrlHeadNode head;
    if (!cache)
    {
        PORT_Assert(0);
        PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
        return SECFailure;
    }

    memset(&head, 0, sizeof(head));
    head.arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    rv = pk11_RetrieveCrls(&head, cache->subject, wincx);


    if (SECFailure == rv)
    {

        cache->invalid |= CRL_CACHE_LAST_FETCH_FAILED;
    } else
    {

        cache->invalid &= (~CRL_CACHE_LAST_FETCH_FAILED);
    }


    if (SECSuccess == rv)
    {
        CERTCrlNode* crlNode = NULL;

        for (crlNode = head.first; crlNode ; crlNode = crlNode->next)
        {
            CachedCrl* returned = NULL;
            CERTSignedCrl* crlobject = crlNode->crl;
            if (!crlobject)
            {
                PORT_Assert(0);
                continue;
            }
            rv = CachedCrl_Create(&returned, crlobject, CRL_OriginToken);
            if (SECSuccess == rv)
            {
                PRBool added = PR_FALSE;
                rv = DPCache_AddCRL(cache, returned, &added);
                if (PR_TRUE != added)
                {
                    rv = CachedCrl_Destroy(returned);
                    returned = NULL;
                }
                else if (vfdate)
                {
                    rv = CachedCrl_Verify(cache, returned, vfdate, wincx);
                }
            }
            else
            {


                cache->invalid |= CRL_CACHE_LAST_FETCH_FAILED;
            }
            if (SECFailure == rv)
            {
                break;
            }
        }
    }

    if (head.arena)
    {
        CERTCrlNode* crlNode = NULL;


        for (crlNode = head.first; crlNode ; crlNode = crlNode->next)
        {
            if (crlNode->crl)
            {
                SEC_DestroyCrl(crlNode->crl);


            }
        }
        PORT_FreeArena(head.arena, PR_FALSE);
    }

    return rv;
}
