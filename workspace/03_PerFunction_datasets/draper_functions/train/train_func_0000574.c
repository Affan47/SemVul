pkix_CertSelector_Match_ExtendedKeyUsage(
        PKIX_ComCertSelParams *params,
        PKIX_PL_Cert *cert,
        PKIX_Boolean *pResult,
        void *plContext)
{
        PKIX_List *extKeyUsageList = NULL;
        PKIX_List *certExtKeyUsageList = NULL;
        PKIX_PL_OID *ekuOid = NULL;
        PKIX_Boolean isContained = PKIX_FALSE;
        PKIX_UInt32 numItems = 0;
        PKIX_UInt32 i;

        PKIX_ENTER(CERTSELECTOR, "pkix_CertSelector_Match_ExtendedKeyUsage");
        PKIX_NULLCHECK_THREE(params, cert, pResult);

        PKIX_CHECK(PKIX_ComCertSelParams_GetExtendedKeyUsage
                    (params, &extKeyUsageList, plContext),
                    PKIX_COMCERTSELPARAMSGETEXTENDEDKEYUSAGEFAILED);

        if (extKeyUsageList == NULL) {
                goto cleanup;
        }

        PKIX_CHECK(PKIX_PL_Cert_GetExtendedKeyUsage
                    (cert, &certExtKeyUsageList, plContext),
                    PKIX_CERTGETEXTENDEDKEYUSAGEFAILED);

        if (certExtKeyUsageList != NULL) {

            PKIX_CHECK(PKIX_List_GetLength
                    (extKeyUsageList, &numItems, plContext),
                    PKIX_LISTGETLENGTHFAILED);

            for (i = 0; i < numItems; i++) {

                PKIX_CHECK(PKIX_List_GetItem
                    (extKeyUsageList, i, (PKIX_PL_Object **)&ekuOid, plContext),
                    PKIX_LISTGETITEMFAILED);

                PKIX_CHECK(pkix_List_Contains
                    (certExtKeyUsageList,
                    (PKIX_PL_Object *)ekuOid,
                    &isContained,
                    plContext),
                    PKIX_LISTCONTAINSFAILED);

                PKIX_DECREF(ekuOid);

                if (isContained != PKIX_TRUE) {
                    *pResult = PKIX_FALSE;
                    PKIX_ERROR(PKIX_CERTSELECTORMATCHEXTENDEDKEYUSAGEFAILED);
                }
            }
        }

cleanup:

        PKIX_DECREF(ekuOid);
        PKIX_DECREF(extKeyUsageList);
        PKIX_DECREF(certExtKeyUsageList);

        PKIX_RETURN(CERTSELECTOR);
}
