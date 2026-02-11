NSC_Verify(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData,
    CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen)
{
    SFTKSession *session;
    SFTKSessionContext *context;
    CK_RV crv;

    CHECK_FORK();


    crv = sftk_GetContext(hSession,&context,SFTK_VERIFY,PR_FALSE,&session);
    if (crv != CKR_OK) return crv;


    if (context->multi) {

	if( CKR_OK == (crv = NSC_VerifyUpdate(hSession, pData, ulDataLen)))
            crv = NSC_VerifyFinal(hSession, pSignature, ulSignatureLen);
    } else {
        if (SECSuccess != (*context->verify)(context->cipherInfo,pSignature,
                                             ulSignatureLen, pData, ulDataLen))
            crv = sftk_MapCryptError(PORT_GetError());

        sftk_TerminateOp( session, SFTK_VERIFY, context );
    }
    sftk_FreeSession(session);
    return crv;
}
