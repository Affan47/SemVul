NSC_SignRecoverInit(CK_SESSION_HANDLE hSession,
			 CK_MECHANISM_PTR pMechanism,CK_OBJECT_HANDLE hKey)
{
    CHECK_FORK();

    switch (pMechanism->mechanism) {
    case CKM_RSA_PKCS:
    case CKM_RSA_X_509:
	return NSC_SignInit(hSession,pMechanism,hKey);
    default:
	break;
    }
    return CKR_MECHANISM_INVALID;
}
