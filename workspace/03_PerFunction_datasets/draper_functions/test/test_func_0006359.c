pkix_ProcessingParams_Equals(
        PKIX_PL_Object *first,
        PKIX_PL_Object *second,
        PKIX_Boolean *pResult,
        void *plContext)
{
        PKIX_UInt32 secondType;
        PKIX_Boolean cmpResult;
        PKIX_ProcessingParams *firstProcParams = NULL;
        PKIX_ProcessingParams *secondProcParams = NULL;

        PKIX_ENTER(PROCESSINGPARAMS, "pkix_ProcessingParams_Equals");
        PKIX_NULLCHECK_THREE(first, second, pResult);

        PKIX_CHECK(pkix_CheckType(first, PKIX_PROCESSINGPARAMS_TYPE, plContext),
                    PKIX_FIRSTOBJECTNOTPROCESSINGPARAMS);

        PKIX_CHECK(PKIX_PL_Object_GetType(second, &secondType, plContext),
                    PKIX_COULDNOTGETTYPEOFSECONDARGUMENT);

        *pResult = PKIX_FALSE;

        if (secondType != PKIX_PROCESSINGPARAMS_TYPE) goto cleanup;

        firstProcParams = (PKIX_ProcessingParams *)first;
        secondProcParams = (PKIX_ProcessingParams *)second;


        if ((firstProcParams->qualifiersRejected) !=
            (secondProcParams->qualifiersRejected)) {
                goto cleanup;
        }

        if (firstProcParams->isCrlRevocationCheckingEnabled !=
            secondProcParams->isCrlRevocationCheckingEnabled) {
                goto cleanup;
        }
        if (firstProcParams->isCrlRevocationCheckingEnabledWithNISTPolicy !=
            secondProcParams->isCrlRevocationCheckingEnabledWithNISTPolicy) {
                goto cleanup;
        }


        PKIX_EQUALS
                (firstProcParams->trustAnchors,
                secondProcParams->trustAnchors,
                &cmpResult,
                plContext,
                PKIX_OBJECTEQUALSFAILED);

        if (!cmpResult) goto cleanup;

        PKIX_EQUALS
                (firstProcParams->hintCerts,
                secondProcParams->hintCerts,
                &cmpResult,
                plContext,
                PKIX_OBJECTEQUALSFAILED);

        if (!cmpResult) goto cleanup;

        PKIX_EQUALS
                (firstProcParams->date,
                secondProcParams->date,
                &cmpResult,
                plContext,
                PKIX_OBJECTEQUALSFAILED);

        if (!cmpResult) goto cleanup;

        PKIX_EQUALS
                (firstProcParams->constraints,
                secondProcParams->constraints,
                &cmpResult,
                plContext,
                PKIX_OBJECTEQUALSFAILED);

        if (!cmpResult) goto cleanup;

        PKIX_EQUALS
                (firstProcParams->initialPolicies,
                secondProcParams->initialPolicies,
                &cmpResult,
                plContext,
                PKIX_OBJECTEQUALSFAILED);

        if (!cmpResult) goto cleanup;


        PKIX_EQUALS
                    ((PKIX_PL_Object *)firstProcParams->certStores,
                    (PKIX_PL_Object *)secondProcParams->certStores,
                    &cmpResult,
                    plContext,
                    PKIX_OBJECTEQUALSFAILED);

        if (!cmpResult) goto cleanup;

        PKIX_EQUALS
                (firstProcParams->resourceLimits,
                secondProcParams->resourceLimits,
                &cmpResult,
                plContext,
                PKIX_OBJECTEQUALSFAILED);

        if (cmpResult == PKIX_FALSE) {
                *pResult = PKIX_FALSE;
                goto cleanup;
        }

        *pResult = cmpResult;

cleanup:

        PKIX_RETURN(PROCESSINGPARAMS);
}
