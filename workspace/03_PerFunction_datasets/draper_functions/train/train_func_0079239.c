CERT_CacheCRL(CERTCertDBHandle* dbhandle, SECItem* newdercrl)
{
    CRLDPCache* cache = NULL;
    SECStatus rv = SECSuccess;
    PRBool writeLocked = PR_FALSE;
    PRBool readlocked;
    CachedCrl* returned = NULL;
    PRBool added = PR_FALSE;
    CERTSignedCrl* newcrl = NULL;
    int realerror = 0;

    if (!dbhandle || !newdercrl)
    {
        PORT_SetError(SEC_ERROR_INVALID_ARGS);
        return SECFailure;
    }


    newcrl = CERT_DecodeDERCrlWithFlags(NULL, newdercrl, SEC_CRL_TYPE,
                                        CRL_DECODE_DONT_COPY_DER |
                                        CRL_DECODE_SKIP_ENTRIES);

    if (!newcrl)
    {
        return SECFailure;
    }


    rv = AcquireDPCache(NULL,
                        &newcrl->crl.derName,
                        NULL, 0, NULL, &cache, &writeLocked);
    if (SECSuccess == rv)
    {
        readlocked = (writeLocked == PR_TRUE? PR_FALSE : PR_TRUE);

        rv = CachedCrl_Create(&returned, newcrl, CRL_OriginExplicit);
        if (SECSuccess == rv && returned)
        {
            DPCache_LockWrite();
            rv = DPCache_AddCRL(cache, returned, &added);
            if (PR_TRUE != added)
            {
                realerror = PORT_GetError();
                CachedCrl_Destroy(returned);
                returned = NULL;
            }
            DPCache_UnlockWrite();
        }

        ReleaseDPCache(cache, writeLocked);

        if (!added)
        {
            rv = SECFailure;
        }
    }
    SEC_DestroyCrl(newcrl);


    if (realerror)
    {
        PORT_SetError(realerror);
    }
    return rv;
}
