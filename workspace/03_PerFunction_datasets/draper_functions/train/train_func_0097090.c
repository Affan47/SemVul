pkix_pl_CRLEntry_Hashcode(
        PKIX_PL_Object *object,
        PKIX_UInt32 *pHashcode,
        void *plContext)
{
        SECItem *nssDate = NULL;
        PKIX_PL_CRLEntry *crlEntry = NULL;
        PKIX_UInt32 crlEntryHash;
        PKIX_UInt32 hashValue;
        PKIX_Int32 reasonCode = 0;

        PKIX_ENTER(CRLENTRY, "pkix_pl_CRLEntry_Hashcode");
        PKIX_NULLCHECK_TWO(object, pHashcode);

        PKIX_CHECK(pkix_CheckType(object, PKIX_CRLENTRY_TYPE, plContext),
                    PKIX_OBJECTNOTCRLENTRY);

        crlEntry = (PKIX_PL_CRLEntry *)object;

        PKIX_NULLCHECK_ONE(crlEntry->nssCrlEntry);
        nssDate = &(crlEntry->nssCrlEntry->revocationDate);

        PKIX_NULLCHECK_ONE(nssDate->data);

        PKIX_CHECK(pkix_hash
                ((const unsigned char *)nssDate->data,
                nssDate->len,
                &crlEntryHash,
                plContext),
                PKIX_ERRORGETTINGHASHCODE);

        PKIX_CHECK(PKIX_PL_Object_Hashcode
                ((PKIX_PL_Object *)crlEntry->serialNumber,
                &hashValue,
                plContext),
                PKIX_OBJECTHASHCODEFAILED);

        crlEntryHash += (hashValue << 7);

        hashValue = 0;

        if (crlEntry->nssCrlEntry->extensions) {

                PKIX_CHECK(pkix_pl_CRLEntry_Extensions_Hashcode
                    (crlEntry->nssCrlEntry->extensions, &hashValue, plContext),
                    PKIX_CRLENTRYEXTENSIONSHASHCODEFAILED);
        }

        crlEntryHash += (hashValue << 7);

        PKIX_CHECK(PKIX_PL_CRLEntry_GetCRLEntryReasonCode
                (crlEntry, &reasonCode, plContext),
                PKIX_CRLENTRYGETCRLENTRYREASONCODEFAILED);

        crlEntryHash += (reasonCode + 777) << 3;

        *pHashcode = crlEntryHash;

cleanup:

        PKIX_RETURN(CRLENTRY);
}
