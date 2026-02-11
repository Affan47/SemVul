PKIX_PL_Cert_GetNameConstraints(
        PKIX_PL_Cert *cert,
        PKIX_PL_CertNameConstraints **pNameConstraints,
        void *plContext)
{
        PKIX_PL_CertNameConstraints *nameConstraints = NULL;

        PKIX_ENTER(CERT, "PKIX_PL_Cert_GetNameConstraints");
        PKIX_NULLCHECK_THREE(cert, cert->nssCert, pNameConstraints);


        if (cert->nameConstraints == NULL && !cert->nameConstraintsAbsent) {

                PKIX_OBJECT_LOCK(cert);

                if (cert->nameConstraints == NULL &&
                    !cert->nameConstraintsAbsent) {

                        PKIX_CHECK(pkix_pl_CertNameConstraints_Create
                                (cert->nssCert, &nameConstraints, plContext),
                                PKIX_CERTNAMECONSTRAINTSCREATEFAILED);

                        if (nameConstraints == NULL) {
                                cert->nameConstraintsAbsent = PKIX_TRUE;
                        }

                        cert->nameConstraints = nameConstraints;
                }

                PKIX_OBJECT_UNLOCK(cert);

        }

        PKIX_INCREF(cert->nameConstraints);

        *pNameConstraints = cert->nameConstraints;

cleanup:
	PKIX_OBJECT_UNLOCK(lockedObject);
        PKIX_RETURN(CERT);
}
