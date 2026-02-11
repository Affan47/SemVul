FC_GenerateKey(CK_SESSION_HANDLE hSession,
    CK_MECHANISM_PTR pMechanism,CK_ATTRIBUTE_PTR pTemplate,CK_ULONG ulCount,
    						CK_OBJECT_HANDLE_PTR phKey) {
    CK_BBOOL *boolptr;

    SFTK_FIPSCHECK();
    CHECK_FORK();


    boolptr = (CK_BBOOL *) fc_getAttribute(pTemplate, ulCount, CKA_SENSITIVE);
    if (boolptr != NULL) {
	if (!(*boolptr)) {
	    return CKR_ATTRIBUTE_VALUE_INVALID;
	}
    }

    rv = NSC_GenerateKey(hSession,pMechanism,pTemplate,ulCount,phKey);
    if (sftk_audit_enabled) {
	sftk_AuditGenerateKey(hSession,pMechanism,pTemplate,ulCount,phKey,rv);
    }
    return rv;
}
