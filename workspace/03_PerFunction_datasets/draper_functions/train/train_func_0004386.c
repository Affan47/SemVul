NSC_DigestUpdate(CK_SESSION_HANDLE hSession,CK_BYTE_PTR pPart,
					    CK_ULONG ulPartLen)
{
    SFTKSessionContext *context;
    CK_RV crv;

    CHECK_FORK();


    crv = sftk_GetContext(hSession,&context,SFTK_HASH,PR_TRUE,NULL);
    if (crv != CKR_OK) return crv;

    (*context->hashUpdate)(context->cipherInfo, pPart, ulPartLen);
    return CKR_OK;
}
