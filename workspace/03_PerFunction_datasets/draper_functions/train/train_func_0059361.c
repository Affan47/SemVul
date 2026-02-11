pkix_SignatureCheckerState_Destroy(
        PKIX_PL_Object *object,
        void *plContext)
{
        pkix_SignatureCheckerState *state = NULL;

        PKIX_ENTER(SIGNATURECHECKERSTATE,
                    "pkix_SignatureCheckerState_Destroy");
        PKIX_NULLCHECK_ONE(object);


        PKIX_CHECK(pkix_CheckType
                    (object, PKIX_SIGNATURECHECKERSTATE_TYPE, plContext),
                    PKIX_OBJECTNOTSIGNATURECHECKERSTATE);

        state = (pkix_SignatureCheckerState *) object;

        state->prevCertCertSign = PKIX_FALSE;

        PKIX_DECREF(state->prevPublicKey);
        PKIX_DECREF(state->prevPublicKeyList);
        PKIX_DECREF(state->keyUsageOID);

cleanup:

        PKIX_RETURN(SIGNATURECHECKERSTATE);
}
