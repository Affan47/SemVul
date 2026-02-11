pkix_pl_CRL_Destroy(
        PKIX_PL_Object *object,
        void *plContext)
{
        PKIX_PL_CRL *crl = NULL;

        PKIX_ENTER(CRL, "pkix_pl_CRL_Destroy");
        PKIX_NULLCHECK_ONE(object);

        PKIX_CHECK(pkix_CheckType(object, PKIX_CRL_TYPE, plContext),
                    PKIX_OBJECTNOTCRL);

        crl = (PKIX_PL_CRL*)object;

        PKIX_CRL_DEBUG("\t\tCalling CERT_DestroyCrl\n");
        if (crl->nssSignedCrl) {
            CERT_DestroyCrl(crl->nssSignedCrl);
        }
        if (crl->adoptedDerCrl) {
            SECITEM_FreeItem(crl->adoptedDerCrl, PR_TRUE);
        }
        crl->nssSignedCrl = NULL;
        crl->adoptedDerCrl = NULL;
        crl->crlNumberAbsent = PKIX_FALSE;

        PKIX_DECREF(crl->issuer);
        PKIX_DECREF(crl->signatureAlgId);
        PKIX_DECREF(crl->crlNumber);
        PKIX_DECREF(crl->crlEntryList);
        PKIX_DECREF(crl->critExtOids);
        if (crl->derGenName) {
            SECITEM_FreeItem(crl->derGenName, PR_TRUE);
        }

cleanup:

        PKIX_RETURN(CRL);
}
