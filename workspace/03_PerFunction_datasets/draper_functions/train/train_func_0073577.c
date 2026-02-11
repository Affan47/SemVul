NSC_VerifyFinal(CK_SESSION_HANDLE hSession,
			CK_BYTE_PTR pSignature,CK_ULONG ulSignatureLen)
{
    SFTKSession *session;
    SFTKSessionContext *context;
    CK_RV crv;

    CHECK_FORK();

    if (!pSignature)
    	return CKR_ARGUMENTS_BAD;


    crv = sftk_GetContext(hSession,&context,SFTK_VERIFY,PR_TRUE,&session);
    if (crv != CKR_OK)
    	return crv;

    if (context->hashInfo) {
        unsigned int digestLen;
        unsigned char tmpbuf[SFTK_MAX_MAC_LENGTH];

        (*context->end)(context->hashInfo, tmpbuf, &digestLen, sizeof(tmpbuf));
        if( SECSuccess != (context->verify)(context->cipherInfo, pSignature,
                                            ulSignatureLen, tmpbuf, digestLen))
            crv = sftk_MapCryptError(PORT_GetError());
    } else if (ulSignatureLen != context->macSize) {

	crv = CKR_SIGNATURE_LEN_RANGE;
    } else if (CKR_OK == (crv = sftk_MACFinal(context))) {
	if (PORT_Memcmp(pSignature, context->macBuf, ulSignatureLen))
	    crv = CKR_SIGNATURE_INVALID;
    }

    sftk_TerminateOp( session, SFTK_VERIFY, context );
    sftk_FreeSession(session);
    return crv;

}
