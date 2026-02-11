pkix_Error_Equals(
        PKIX_PL_Object *firstObject,
        PKIX_PL_Object *secondObject,
        PKIX_Boolean *pResult,
        void *plContext)
{
        PKIX_Error *firstError = NULL;
        PKIX_Error *secondError = NULL;
        PKIX_Error *firstCause = NULL;
        PKIX_Error *secondCause = NULL;
        PKIX_PL_Object *firstInfo = NULL;
        PKIX_PL_Object *secondInfo = NULL;
        PKIX_ERRORCLASS firstClass, secondClass;
        PKIX_UInt32 secondType;
        PKIX_Boolean boolResult, unequalFlag;

        PKIX_ENTER(ERROR, "pkix_Error_Equals");
        PKIX_NULLCHECK_THREE(firstObject, secondObject, pResult);

        unequalFlag = PKIX_FALSE;


        if (firstObject == secondObject) {
                *pResult = PKIX_TRUE;
                goto cleanup;
        } else {

                *pResult = PKIX_FALSE;
        }

        PKIX_CHECK(pkix_CheckType(firstObject, PKIX_ERROR_TYPE, plContext),
                    PKIX_FIRSTOBJECTNOTANERROROBJECT);

        PKIX_CHECK(PKIX_PL_Object_GetType
                    (secondObject, &secondType, plContext),
                    PKIX_ERRORGETTINGSECONDOBJECTTYPE);


        if (secondType != PKIX_ERROR_TYPE) goto cleanup;


        firstError = (PKIX_Error *) firstObject;
        secondError = (PKIX_Error *) secondObject;


        firstClass = firstError->errClass;
        secondClass = secondError->errClass;


        if (firstClass != secondClass) goto cleanup;


        firstCause = firstError->cause;
        secondCause = secondError->cause;


        if (((firstCause != NULL) && (secondCause == NULL))||
            ((firstCause == NULL) && (secondCause != NULL)))
                unequalFlag = PKIX_TRUE;

        if ((firstCause != NULL) && (secondCause != NULL)) {
                PKIX_CHECK(PKIX_PL_Object_Equals
                            ((PKIX_PL_Object*)firstCause,
                            (PKIX_PL_Object*)secondCause,
                            &boolResult,
                            plContext),
                            PKIX_ERRORINRECURSIVEEQUALSCALL);


                if (boolResult == 0) unequalFlag = PKIX_TRUE;
        }


        if (unequalFlag) goto cleanup;


        firstInfo = firstError->info;
        secondInfo = secondError->info;

        if (firstInfo != secondInfo) goto cleanup;


        if (((firstInfo != NULL) && (secondInfo == NULL))||
            ((firstInfo == NULL) && (secondInfo != NULL)))
                unequalFlag = PKIX_TRUE;

        if ((firstInfo != NULL) && (secondInfo != NULL)) {

                PKIX_CHECK(PKIX_PL_Object_Equals
                            ((PKIX_PL_Object*)firstInfo,
                            (PKIX_PL_Object*)secondInfo,
                            &boolResult,
                            plContext),
                            PKIX_ERRORINRECURSIVEEQUALSCALL);


                if (boolResult == 0) unequalFlag = PKIX_TRUE;
        }


        if (unequalFlag) goto cleanup;


        if (firstError->errCode != secondError->errCode) {
                unequalFlag = PKIX_TRUE;
        }

        if (firstError->plErr != secondError->plErr) {
                unequalFlag = PKIX_TRUE;
        }


        if (unequalFlag) goto cleanup;


        *pResult = PKIX_TRUE;

cleanup:

        PKIX_RETURN(ERROR);
}
