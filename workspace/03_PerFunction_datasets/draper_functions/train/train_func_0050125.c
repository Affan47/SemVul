FC_InitToken(CK_SLOT_ID slotID,CK_CHAR_PTR pPin,
 				CK_ULONG usPinLen,CK_CHAR_PTR pLabel) {
    CK_RV crv;

    CHECK_FORK();

    crv = NSC_InitToken(slotID,pPin,usPinLen,pLabel);
    if (sftk_audit_enabled) {
	char msg[128];
	NSSAuditSeverity severity = (crv == CKR_OK) ?
		NSS_AUDIT_INFO : NSS_AUDIT_ERROR;

	PR_snprintf(msg,sizeof msg,
		"C_InitToken(slotID=%lu, pLabel=\"%.32s\")=0x%08lX",
		(PRUint32)slotID,pLabel,(PRUint32)crv);
	sftk_LogAuditMessage(severity, NSS_AUDIT_INIT_TOKEN, msg);
    }
    return crv;
}
