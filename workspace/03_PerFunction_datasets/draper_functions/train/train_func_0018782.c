SEC_PKCS7DecoderUpdate(SEC_PKCS7DecoderContext *p7dcx,
		       const char *buf, unsigned long len)
{
    if (p7dcx->cinfo != NULL && p7dcx->dcx != NULL) {
	PORT_Assert (p7dcx->error == 0);
	if (p7dcx->error == 0) {
	    if (SEC_ASN1DecoderUpdate (p7dcx->dcx, buf, len) != SECSuccess) {
		p7dcx->error = PORT_GetError();
		PORT_Assert (p7dcx->error);
		if (p7dcx->error == 0)
		    p7dcx->error = -1;
	    }
	}
    }

    if (p7dcx->error) {
	if (p7dcx->dcx != NULL) {
	    (void) SEC_ASN1DecoderFinish (p7dcx->dcx);
	    p7dcx->dcx = NULL;
	}
	if (p7dcx->cinfo != NULL) {
	    SEC_PKCS7DestroyContentInfo (p7dcx->cinfo);
	    p7dcx->cinfo = NULL;
	}
	PORT_SetError (p7dcx->error);
	return SECFailure;
    }

    return SECSuccess;
}
