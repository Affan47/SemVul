FC_DestroyObject(CK_SESSION_HANDLE hSession,
		 				CK_OBJECT_HANDLE hObject) {
    CK_RV rv;
    CK_OBJECT_CLASS objClass = CKO_NOT_A_KEY;

    CHECK_FORK();

    SFTK_FIPSFATALCHECK();
    rv = sftk_get_object_class_and_fipsCheck(hSession, hObject, &objClass);
    if (rv == CKR_OK) {
	rv = NSC_DestroyObject(hSession,hObject);
    }
    if (sftk_audit_enabled && SFTK_IS_KEY_OBJECT(objClass)) {
	sftk_AuditDestroyObject(hSession,hObject,rv);
    }
    return rv;
}
