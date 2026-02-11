PKIX_PL_Cert_IsCertTrusted(
        PKIX_PL_Cert *cert,
        PKIX_PL_TrustAnchorMode trustAnchorMode,
        PKIX_Boolean *pTrusted,
        void *plContext)
{
        PKIX_CertStore_CheckTrustCallback trustCallback = NULL;
        PKIX_Boolean trusted = PKIX_FALSE;
        SECStatus rv = SECFailure;

        PKIX_ENTER(CERT, "PKIX_PL_Cert_IsCertTrusted");
        PKIX_NULLCHECK_TWO(cert, pTrusted);


        rv = pkix_pl_Cert_GetTrusted(plContext, cert, &trusted, PKIX_TRUE);
        if (rv != SECSuccess) {


                *pTrusted = PKIX_FALSE;
                PKIX_ERROR(PKIX_CERTISCERTTRUSTEDFAILED);
        }

        if (trustAnchorMode == PKIX_PL_TrustAnchorMode_Exclusive ||
            (trustAnchorMode == PKIX_PL_TrustAnchorMode_Additive &&
             cert->isUserTrustAnchor)) {

            *pTrusted = cert->isUserTrustAnchor;
            goto cleanup;
        }


        if (plContext == NULL || cert->store == NULL) {
                *pTrusted = PKIX_FALSE;
                goto cleanup;
        }

        PKIX_CHECK(PKIX_CertStore_GetTrustCallback
                (cert->store, &trustCallback, plContext),
                PKIX_CERTSTOREGETTRUSTCALLBACKFAILED);

        PKIX_CHECK_ONLY_FATAL(trustCallback
                (cert->store, cert, &trusted, plContext),
                PKIX_CHECKTRUSTCALLBACKFAILED);


        if (PKIX_ERROR_RECEIVED || (trusted == PKIX_FALSE)) {
                *pTrusted = PKIX_FALSE;
                goto cleanup;
        }

        *pTrusted = trusted;

cleanup:
        PKIX_RETURN(CERT);
}
