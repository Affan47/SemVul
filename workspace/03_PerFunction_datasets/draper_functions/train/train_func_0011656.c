cert_CheckCertRevocationStatus(CERTCertificate* cert, CERTCertificate* issuer,
                               const SECItem* dp, PRTime t, void *wincx,
                               CERTRevocationStatus *revStatus,
                               CERTCRLEntryReasonCode *revReason)
{
    PRBool lockedwrite = PR_FALSE;
    SECStatus rv = SECSuccess;
    CRLDPCache* dpcache = NULL;
    CERTRevocationStatus status = certRevocationStatusRevoked;
    CERTCRLEntryReasonCode reason = crlEntryReasonUnspecified;
    CERTCrlEntry* entry = NULL;
    dpcacheStatus ds;

    if (!cert || !issuer)
    {
        PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
        return SECFailure;
    }

    if (revStatus)
    {
        *revStatus = status;
    }
    if (revReason)
    {
        *revReason = reason;
    }

    if (t && secCertTimeValid != CERT_CheckCertValidTimes(issuer, t, PR_FALSE))
    {


        PORT_SetError(SEC_ERROR_EXPIRED_ISSUER_CERTIFICATE);
        return SECFailure;
    }

    rv = AcquireDPCache(issuer, &issuer->derSubject, dp, t, wincx, &dpcache,
                        &lockedwrite);
    PORT_Assert(SECSuccess == rv);
    if (SECSuccess != rv)
    {
        PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
        return SECFailure;
    }

    ds = DPCache_Lookup(dpcache, &cert->serialNumber, &entry);
    switch (ds)
    {
        case dpcacheFoundEntry:
            PORT_Assert(entry);

            if (entry->revocationDate.data && entry->revocationDate.len)
            {
                PRTime revocationDate = 0;
                if (SECSuccess == DER_DecodeTimeChoice(&revocationDate,
                                               &entry->revocationDate))
                {


                    if (t>=revocationDate)
                    {
                        rv = SECFailure;
                    }
                    else
                    {
                        status = certRevocationStatusValid;
                    }
                }
                else
                {


                    rv = SECFailure;
                }
            }
            else
            {

                rv = SECFailure;
            }
            if (SECFailure == rv)
            {
                SECStatus rv2 = CERT_FindCRLEntryReasonExten(entry, &reason);
                PORT_SetError(SEC_ERROR_REVOKED_CERTIFICATE);
            }
            break;

        case dpcacheEmpty:

            status = certRevocationStatusUnknown;
            break;

        case dpcacheNoEntry:
            status = certRevocationStatusValid;
            break;

        case dpcacheInvalidCacheError:


            status = certRevocationStatusUnknown;
            break;

        default:

            break;
    }

    ReleaseDPCache(dpcache, lockedwrite);
    if (revStatus)
    {
        *revStatus = status;
    }
    if (revReason)
    {
        *revReason = reason;
    }
    return rv;
}
