AddPolicyConstraints(void *extHandle)
{
    CERTCertificatePolicyConstraints *policyConstr;
    PLArenaPool *arena = NULL;
    SECStatus rv = SECSuccess;
    SECItem *item, *dummy;
    char buffer[512];
    int value;
    PRBool yesNoAns;
    PRBool skipExt = PR_TRUE;

    arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    if ( !arena ) {
        SECU_PrintError(progName, "out of memory");
        return SECFailure;
    }

    policyConstr = PORT_ArenaZNew(arena, CERTCertificatePolicyConstraints);
    if (policyConstr == NULL) {
        SECU_PrintError(progName, "out of memory");
        goto loser;
    }

    if (PrintChoicesAndGetAnswer("for requireExplicitPolicy enter the number "
               "of certs in path\nbefore explicit policy is required\n"
               "(press Enter to omit)", buffer, sizeof(buffer)) == SECFailure) {
        goto loser;
    }

    if (PORT_Strlen(buffer)) {
        value = PORT_Atoi(buffer);
	if (value < 0) {
            goto loser;
        }
        item = &policyConstr->explicitPolicySkipCerts;
        dummy = SEC_ASN1EncodeInteger(arena, item, value);
        if (!dummy) {
            goto loser;
        }
        skipExt = PR_FALSE;
    }

    if (PrintChoicesAndGetAnswer("for inihibitPolicyMapping enter "
               "the number of certs in path\n"
	       "after which policy mapping is not allowed\n"
               "(press Enter to omit)", buffer, sizeof(buffer)) == SECFailure) {
        goto loser;
    }

    if (PORT_Strlen(buffer)) {
        value = PORT_Atoi(buffer);
	if (value < 0) {
            goto loser;
        }
        item = &policyConstr->inhibitMappingSkipCerts;
        dummy = SEC_ASN1EncodeInteger(arena, item, value);
        if (!dummy) {
            goto loser;
        }
        skipExt = PR_FALSE;
    }


    if (!skipExt) {
        yesNoAns = GetYesNo("Is this a critical extension [y/N]?");

        rv = SECU_EncodeAndAddExtensionValue(arena, extHandle, policyConstr,
	     yesNoAns, SEC_OID_X509_POLICY_CONSTRAINTS,
	     (EXTEN_EXT_VALUE_ENCODER)CERT_EncodePolicyConstraintsExtension);
    } else {
	fprintf(stdout, "Policy Constraint extensions must contain "
                        "at least one policy field\n");
	rv = SECFailure;
    }

loser:
    if (arena) {
        PORT_FreeArena (arena, PR_FALSE);
    }
    return (rv);
}
