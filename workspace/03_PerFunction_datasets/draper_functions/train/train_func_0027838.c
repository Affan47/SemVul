pkix_BasicConstraintsChecker_Initialize(
        PKIX_UInt32 certsRemaining,
        PKIX_CertChainChecker **pChecker,
        void *plContext)
{
        pkix_BasicConstraintsCheckerState *state = NULL;

        PKIX_ENTER(CERTCHAINCHECKER, "pkix_BasicConstraintsChecker_Initialize");
        PKIX_NULLCHECK_ONE(pChecker);

        PKIX_CHECK(pkix_BasicConstraintsCheckerState_Create
                    (certsRemaining, &state, plContext),
                    PKIX_BASICCONSTRAINTSCHECKERSTATECREATEFAILED);

        PKIX_CHECK(PKIX_CertChainChecker_Create
                    (pkix_BasicConstraintsChecker_Check,
                    PKIX_FALSE,
                    PKIX_FALSE,
                    NULL,
                    (PKIX_PL_Object *)state,
                    pChecker,
                    plContext),
                    PKIX_CERTCHAINCHECKERCHECKFAILED);

cleanup:
        PKIX_DECREF(state);

        PKIX_RETURN(CERTCHAINCHECKER);
}
