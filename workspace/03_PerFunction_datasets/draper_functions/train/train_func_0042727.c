FC_VerifyRecoverInit(CK_SESSION_HANDLE hSession,
			CK_MECHANISM_PTR pMechanism,CK_OBJECT_HANDLE hKey) {
    SFTK_FIPSCHECK();
    CHECK_FORK();

    rv = NSC_VerifyRecoverInit(hSession,pMechanism,hKey);
    if (sftk_audit_enabled) {
	sftk_AuditCryptInit("VerifyRecover",hSession,pMechanism,hKey,rv);
    }
    return rv;
}
