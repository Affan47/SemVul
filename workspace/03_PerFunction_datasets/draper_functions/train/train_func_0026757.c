pkix_Error_ToString(
        PKIX_PL_Object *object,
        PKIX_PL_String **pString,
        void *plContext)
{
        PKIX_Error *error = NULL;
        PKIX_Error *cause = NULL;
        PKIX_PL_String *desc = NULL;
        PKIX_PL_String *formatString = NULL;
        PKIX_PL_String *causeString = NULL;
        PKIX_PL_String *optCauseString = NULL;
        PKIX_PL_String *errorNameString = NULL;
        char *format = NULL;
        PKIX_ERRORCLASS errClass;

        PKIX_ENTER(ERROR, "pkix_Error_ToString");
        PKIX_NULLCHECK_TWO(object, pString);

        PKIX_CHECK(pkix_CheckType(object, PKIX_ERROR_TYPE, plContext),
                PKIX_OBJECTNOTANERROR);

        error = (PKIX_Error *)object;


        errClass = error->errClass;


        PKIX_Error_GetDescription(error, &desc, plContext);


        cause = error->cause;


        if (cause != NULL) {
                pkix_error_cause_depth++;


                PKIX_CHECK(PKIX_PL_Object_ToString
                            ((PKIX_PL_Object*)cause, &causeString, plContext),
                            PKIX_ERRORGETTINGCAUSESTRING);

                format = "\n*** Cause (%d): %s";

                PKIX_CHECK(PKIX_PL_String_Create
                            (PKIX_ESCASCII,
                            format,
                            0,
                            &formatString,
                            plContext),
                            PKIX_STRINGCREATEFAILED);


                PKIX_CHECK(PKIX_PL_Sprintf
                            (&optCauseString,
                            plContext,
                            formatString,
                            pkix_error_cause_depth,
                            causeString),
                            PKIX_SPRINTFFAILED);

                PKIX_DECREF(formatString);

                pkix_error_cause_depth--;
        }


        if (optCauseString != NULL) {
                format = "*** %s Error- %s%s";
        } else {
                format = "*** %s Error- %s";
        }


        if (errClass >= PKIX_NUMERRORCLASSES) {
                errClass = 0;
        }

        PKIX_CHECK(PKIX_PL_String_Create
                    (PKIX_ESCASCII,
                    (void *)PKIX_ERRORCLASSNAMES[errClass],
                    0,
                    &errorNameString,
                    plContext),
                    PKIX_STRINGCREATEFAILED);

        PKIX_CHECK(PKIX_PL_String_Create
                    (PKIX_ESCASCII,
                    format,
                    0,
                    &formatString,
                    plContext),
                    PKIX_STRINGCREATEFAILED);


        PKIX_CHECK(PKIX_PL_Sprintf
                    (pString,
                    plContext,
                    formatString,
                    errorNameString,
                    desc,
                    optCauseString),
                    PKIX_SPRINTFFAILED);

cleanup:

        PKIX_DECREF(desc);
        PKIX_DECREF(causeString);
        PKIX_DECREF(formatString);
        PKIX_DECREF(optCauseString);
        PKIX_DECREF(errorNameString);

        PKIX_RETURN(ERROR);
}
