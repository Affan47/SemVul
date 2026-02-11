NSC_SignRecover(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData,
  CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen)
{
    CHECK_FORK();

    return NSC_Sign(hSession,pData,ulDataLen,pSignature,pulSignatureLen);
}
