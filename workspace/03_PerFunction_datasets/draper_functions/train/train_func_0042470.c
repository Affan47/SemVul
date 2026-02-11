pkix_pl_CertPolicyMap_ToString(
        PKIX_PL_Object *object,
        PKIX_PL_String **pString,
        void *plContext)
{
        PKIX_PL_CertPolicyMap *certMap = NULL;
        PKIX_PL_String *format = NULL;
        PKIX_PL_String *outString = NULL;
        PKIX_PL_String *issuerString = NULL;
        PKIX_PL_String *subjectString = NULL;

        PKIX_ENTER(CERTPOLICYMAP, "pkix_pl_CertPolicyMap_ToString");

        PKIX_NULLCHECK_TWO(object, pString);

        PKIX_CHECK(pkix_CheckType(object, PKIX_CERTPOLICYMAP_TYPE, plContext),
                PKIX_OBJECTNOTCERTPOLICYMAP);

        certMap = (PKIX_PL_CertPolicyMap *)object;

        PKIX_TOSTRING
                (certMap->issuerDomainPolicy,
                &issuerString,
                plContext,
                PKIX_OBJECTTOSTRINGFAILED);

        PKIX_TOSTRING
                (certMap->subjectDomainPolicy,
                &subjectString,
                plContext,
                PKIX_OBJECTTOSTRINGFAILED);


        PKIX_CHECK(PKIX_PL_String_Create
                (PKIX_ESCASCII, "%s=>%s", 0, &format, plContext),
                PKIX_ERRORINSTRINGCREATE);

        PKIX_CHECK(PKIX_PL_Sprintf
                (&outString, plContext, format, issuerString, subjectString),
                PKIX_ERRORINSPRINTF);

        *pString = outString;

cleanup:
        PKIX_DECREF(format);
        PKIX_DECREF(issuerString);
        PKIX_DECREF(subjectString);

        PKIX_RETURN(CERTPOLICYMAP);
}
