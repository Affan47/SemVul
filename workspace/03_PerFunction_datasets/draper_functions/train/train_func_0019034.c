pkix_pl_OcspRequest_Equals(
        PKIX_PL_Object *firstObj,
        PKIX_PL_Object *secondObj,
        PKIX_Boolean *pResult,
        void *plContext)
{
        PKIX_Boolean match = PKIX_FALSE;
        PKIX_UInt32 secondType = 0;
        PKIX_PL_OcspRequest *firstReq = NULL;
        PKIX_PL_OcspRequest *secondReq = NULL;

        PKIX_ENTER(OCSPREQUEST, "pkix_pl_OcspRequest_Equals");
        PKIX_NULLCHECK_THREE(firstObj, secondObj, pResult);


        PKIX_CHECK(pkix_CheckType(firstObj, PKIX_OCSPREQUEST_TYPE, plContext),
                    PKIX_FIRSTOBJARGUMENTNOTOCSPREQUEST);


        if (firstObj == secondObj){
                match = PKIX_TRUE;
                goto cleanup;
        }


        PKIX_CHECK(PKIX_PL_Object_GetType
                    (secondObj, &secondType, plContext),
                    PKIX_COULDNOTGETTYPEOFSECONDARGUMENT);
        if (secondType != PKIX_OCSPREQUEST_TYPE) {
                goto cleanup;
        }

        firstReq = (PKIX_PL_OcspRequest *)firstObj;
        secondReq = (PKIX_PL_OcspRequest *)secondObj;

        if (firstReq->addServiceLocator != secondReq->addServiceLocator) {
                goto cleanup;
        }

        PKIX_EQUALS(firstReq->cert, secondReq->cert, &match, plContext,
                PKIX_CERTEQUALSFAILED);

        if (match == PKIX_FALSE) {
                goto cleanup;
        }

        PKIX_EQUALS(firstReq->validity, secondReq->validity, &match, plContext,
                PKIX_DATEEQUALSFAILED);

        if (match == PKIX_FALSE) {
                goto cleanup;
        }

        PKIX_EQUALS
                (firstReq->signerCert, secondReq->signerCert, &match, plContext,
                PKIX_CERTEQUALSFAILED);

cleanup:

        *pResult = match;

        PKIX_RETURN(OCSPREQUEST);
}
