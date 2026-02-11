GetBestCRL(CRLDPCache* cache, PRBool entries)
{
    CachedCrl* acrl = NULL;

    PORT_Assert(cache);
    if (!cache)
    {
        PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
        return NULL;
    }

    if (0 == cache->ncrls)
    {

        PORT_SetError(SEC_ERROR_CRL_NOT_FOUND);
        return NULL;
    }


    if (cache->selected)
    {
        return SEC_DupCrl(cache->selected->crl);
    }


    acrl = cache->crls[cache->ncrls-1];

    if (acrl && (PR_FALSE == GetOpaqueCRLFields(acrl->crl)->decodingError) )
    {
        SECStatus rv = SECSuccess;
        if (PR_TRUE == entries)
        {
            rv = CERT_CompleteCRLDecodeEntries(acrl->crl);
        }
        if (SECSuccess == rv)
        {
            return SEC_DupCrl(acrl->crl);
        }
    }

    PORT_SetError(SEC_ERROR_CRL_NOT_FOUND);
    return NULL;
}
