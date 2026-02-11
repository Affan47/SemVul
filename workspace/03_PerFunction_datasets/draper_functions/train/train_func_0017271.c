pkix_pl_InfoAccess_ToString(
        PKIX_PL_Object *object,
        PKIX_PL_String **pString,
        void *plContext)
{
        PKIX_PL_InfoAccess *infoAccess;
        PKIX_PL_String *infoAccessString = NULL;
        char *asciiFormat = NULL;
        char *asciiMethod = NULL;
        PKIX_PL_String *formatString = NULL;
        PKIX_PL_String *methodString = NULL;
        PKIX_PL_String *locationString = NULL;

        PKIX_ENTER(INFOACCESS, "pkix_pl_InfoAccess_ToString");
        PKIX_NULLCHECK_TWO(object, pString);

        PKIX_CHECK(pkix_CheckType
                    (object, PKIX_INFOACCESS_TYPE, plContext),
                    PKIX_OBJECTNOTINFOACCESS);

        infoAccess = (PKIX_PL_InfoAccess *)object;

        asciiFormat =
                "["
                "method:%s, "
                "location:%s"
                "]";

        PKIX_CHECK(PKIX_PL_String_Create
                    (PKIX_ESCASCII,
                    asciiFormat,
                    0,
                    &formatString,
                    plContext),
                    PKIX_STRINGCREATEFAILED);

        switch(infoAccess->method) {
            case PKIX_INFOACCESS_CA_ISSUERS:
                    asciiMethod = "caIssuers";
                    break;
            case PKIX_INFOACCESS_OCSP:
                    asciiMethod = "ocsp";
                    break;
            case PKIX_INFOACCESS_TIMESTAMPING:
                    asciiMethod = "timestamping";
                    break;
            case PKIX_INFOACCESS_CA_REPOSITORY:
                    asciiMethod = "caRepository";
                    break;
            default:
                    asciiMethod = "unknown";
        }

        PKIX_CHECK(PKIX_PL_String_Create
                    (PKIX_ESCASCII,
                    asciiMethod,
                    0,
                    &methodString,
                    plContext),
                    PKIX_STRINGCREATEFAILED);

        PKIX_TOSTRING(infoAccess->location, &locationString, plContext,
                    PKIX_GENERALNAMETOSTRINGFAILED);

        PKIX_CHECK(PKIX_PL_Sprintf
                    (&infoAccessString,
                    plContext,
                    formatString,
                    methodString,
                    locationString),
                    PKIX_SPRINTFFAILED);

        *pString = infoAccessString;

cleanup:

        PKIX_DECREF(formatString);
        PKIX_DECREF(methodString);
        PKIX_DECREF(locationString);

        PKIX_RETURN(INFOACCESS);
}
