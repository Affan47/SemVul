pkix_SignatureChecker_Initialize(
        PKIX_PL_PublicKey *trustedPubKey,
        PKIX_UInt32 certsRemaining,
        PKIX_CertChainChecker **pChecker,
        void *plContext)
{
        pkix_SignatureCheckerState* state = NULL;
        PKIX_ENTER(CERTCHAINCHECKER, "PKIX_SignatureChecker_Initialize");
        PKIX_NULLCHECK_TWO(pChecker, trustedPubKey);

        PKIX_CHECK(pkix_SignatureCheckerState_Create
                    (trustedPubKey, certsRemaining, &state, plContext),
                    PKIX_SIGNATURECHECKERSTATECREATEFAILED);

        PKIX_CHECK(PKIX_CertChainChecker_Create
                    (pkix_SignatureChecker_Check,
                    PKIX_FALSE,
                    PKIX_FALSE,
                    NULL,
                    (PKIX_PL_Object *) state,
                    pChecker,
                    plContext),
                    PKIX_CERTCHAINCHECKERCREATEFAILED);

cleanup:

        PKIX_DECREF(state);

        PKIX_RETURN(CERTCHAINCHECKER);

}
