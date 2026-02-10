pkix_pl_CertBasicConstraints_ToString(
        PKIX_PL_Object *object,
        PKIX_PL_String **pString,
        void *plContext)
{
        PKIX_PL_String *certBasicConstraintsString = NULL;
        PKIX_PL_CertBasicConstraints *certB = NULL;
        PKIX_Boolean isCA = PKIX_FALSE;
        PKIX_Int32 pathLen = 0;
        PKIX_PL_String *outString = NULL;
        char *fmtString = NULL;
        PKIX_Boolean pathlenArg = PKIX_FALSE;

        PKIX_ENTER(CERTBASICCONSTRAINTS,
                "pkix_pl_CertBasicConstraints_toString");
        PKIX_NULLCHECK_TWO(object, pString);

        PKIX_CHECK(pkix_CheckType
                    (object, PKIX_CERTBASICCONSTRAINTS_TYPE, plContext),
                    PKIX_FIRSTARGUMENTNOTCERTBASICCONSTRAINTSOBJECT);

        certB = (PKIX_PL_CertBasicConstraints *)object;


        isCA = certB->isCA;

        if (isCA) {
                pathLen = certB->pathLen;

                if (pathLen == CERT_UNLIMITED_PATH_CONSTRAINT) {

                        fmtString = "CA(-1)";
                        pathlenArg = PKIX_FALSE;
                } else {

                        fmtString = "CA(%d)";
                        pathlenArg = PKIX_TRUE;
                }
        } else {

                fmtString = "~CA";
                pathlenArg = PKIX_FALSE;
        }

        PKIX_CHECK(PKIX_PL_String_Create
                    (PKIX_ESCASCII,
                    fmtString,
                    0,
                    &certBasicConstraintsString,
                    plContext),
                    PKIX_STRINGCREATEFAILED);

        if (pathlenArg) {
                PKIX_CHECK(PKIX_PL_Sprintf
                            (&outString,
                            plContext,
                            certBasicConstraintsString,
                            pathLen),
                            PKIX_SPRINTFFAILED);
        } else {
                PKIX_CHECK(PKIX_PL_Sprintf
                            (&outString,
                            plContext,
                            certBasicConstraintsString),
                            PKIX_SPRINTFFAILED);
        }

        *pString = outString;

cleanup:

        PKIX_DECREF(certBasicConstraintsString);

        PKIX_RETURN(CERTBASICCONSTRAINTS);
}
