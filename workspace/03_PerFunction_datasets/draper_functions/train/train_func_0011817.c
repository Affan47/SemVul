pkix_pl_CertBasicConstraints_Create(
        PKIX_Boolean isCA,
        PKIX_Int32 pathLen,
        PKIX_PL_CertBasicConstraints **pObject,
        void *plContext)
{
        PKIX_PL_CertBasicConstraints *basic = NULL;

        PKIX_ENTER(CERTBASICCONSTRAINTS,
                    "pkix_pl_CertBasicConstraints_Create");
        PKIX_NULLCHECK_ONE(pObject);

        PKIX_CHECK(PKIX_PL_Object_Alloc
                    (PKIX_CERTBASICCONSTRAINTS_TYPE,
                    sizeof (PKIX_PL_CertBasicConstraints),
                    (PKIX_PL_Object **)&basic,
                    plContext),
                    PKIX_COULDNOTCREATECERTBASICCONSTRAINTSOBJECT);

        basic->isCA = isCA;


        basic->pathLen = pathLen;

        *pObject = basic;

cleanup:

        PKIX_RETURN(CERTBASICCONSTRAINTS);
}
