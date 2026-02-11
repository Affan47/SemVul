NSC_EncryptUpdate(CK_SESSION_HANDLE hSession,
    CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR pEncryptedPart,
					CK_ULONG_PTR pulEncryptedPartLen)
{
    SFTKSessionContext *context;
    unsigned int outlen,i;
    unsigned int padoutlen = 0;
    unsigned int maxout = *pulEncryptedPartLen;
    CK_RV crv;
    SECStatus rv;

    CHECK_FORK();


    crv = sftk_GetContext(hSession,&context,SFTK_ENCRYPT,PR_TRUE,NULL);
    if (crv != CKR_OK) return crv;

    if (!pEncryptedPart) {
	if (context->doPad) {
	    CK_ULONG totalDataAvailable = ulPartLen + context->padDataLength;
	    CK_ULONG blocksToSend = totalDataAvailable/context->blockSize;

	    *pulEncryptedPartLen = blocksToSend * context->blockSize;
	    return CKR_OK;
	}
	*pulEncryptedPartLen = ulPartLen;
	return CKR_OK;
    }


    if (context->doPad) {

	if (context->padDataLength != 0) {

	    for (i=context->padDataLength;
			(ulPartLen != 0) && i < context->blockSize; i++) {
		context->padBuf[i] = *pPart++;
		ulPartLen--;
		context->padDataLength++;
	    }


	    if (context->padDataLength != context->blockSize) {
		*pulEncryptedPartLen = 0;
		return CKR_OK;
	    }

    	    rv = (*context->update)(context->cipherInfo, pEncryptedPart,
		&padoutlen, context->blockSize, context->padBuf,
							context->blockSize);
	    if (rv != SECSuccess) {
		return sftk_MapCryptError(PORT_GetError());
	    }
	    pEncryptedPart += padoutlen;
	    maxout -= padoutlen;
	}

	context->padDataLength = ulPartLen % context->blockSize;
	if (context->padDataLength) {
	    PORT_Memcpy(context->padBuf,
			&pPart[ulPartLen-context->padDataLength],
							context->padDataLength);
	    ulPartLen -= context->padDataLength;
	}

	if (ulPartLen == 0) {
	    *pulEncryptedPartLen = padoutlen;
	    return CKR_OK;
	}
    }


    rv = (*context->update)(context->cipherInfo,pEncryptedPart,
					&outlen, maxout, pPart, ulPartLen);
    *pulEncryptedPartLen = (CK_ULONG) (outlen + padoutlen);
    return (rv == SECSuccess) ? CKR_OK : sftk_MapCryptError(PORT_GetError());
}
