pkix_pl_CertNameConstraints_CheckNameSpaceNssNames(
        CERTGeneralName *nssSubjectNames,
        PKIX_PL_CertNameConstraints *nameConstraints,
        PKIX_Boolean *pCheckPass,
        void *plContext)
{
        CERTNameConstraints **nssNameConstraintsList = NULL;
        CERTNameConstraints *nssNameConstraints = NULL;
        CERTGeneralName *nssMatchName = NULL;
        PLArenaPool *arena = NULL;
        PKIX_UInt32 numItems = 0;
        PKIX_UInt32 i;
        SECStatus status = SECSuccess;

        PKIX_ENTER(CERTNAMECONSTRAINTS,
                "pkix_pl_CertNameConstraints_CheckNameSpaceNssNames");
        PKIX_NULLCHECK_THREE(nssSubjectNames, nameConstraints, pCheckPass);

        *pCheckPass = PKIX_TRUE;

        PKIX_CERTNAMECONSTRAINTS_DEBUG("\t\tCalling PORT_NewArena\n");
        arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
        if (arena == NULL) {
                PKIX_ERROR(PKIX_OUTOFMEMORY);
        }

        nssMatchName = nssSubjectNames;
        nssNameConstraintsList = nameConstraints->nssNameConstraintsList;


        do {

            numItems = nameConstraints->numNssNameConstraints;

            for (i = 0; i < numItems; i++) {

                PKIX_NULLCHECK_ONE(nssNameConstraintsList);
                nssNameConstraints = *(nssNameConstraintsList + i);
                PKIX_NULLCHECK_ONE(nssNameConstraints);

                PKIX_CERTNAMECONSTRAINTS_DEBUG
                        ("\t\tCalling CERT_CheckNameSpace\n");
                status = CERT_CheckNameSpace
                        (arena, nssNameConstraints, nssMatchName);
                if (status != SECSuccess) {
                        break;
                }

            }

            if (status != SECSuccess) {
                    break;
            }

            PKIX_CERTNAMECONSTRAINTS_DEBUG
                    ("\t\tCalling CERT_GetNextGeneralName\n");
            nssMatchName = CERT_GetNextGeneralName(nssMatchName);

        } while (nssMatchName != nssSubjectNames);

        if (status == SECFailure) {

                *pCheckPass = PKIX_FALSE;
        }

cleanup:

        if (arena){
                PKIX_CERTNAMECONSTRAINTS_DEBUG
                        ("\t\tCalling PORT_FreeArena).\n");
                PORT_FreeArena(arena, PR_FALSE);
        }

        PKIX_RETURN(CERTNAMECONSTRAINTS);
}
