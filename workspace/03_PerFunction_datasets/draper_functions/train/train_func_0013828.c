SEC_PKCS7DecoderFinish(SEC_PKCS7DecoderContext *p7dcx)
{
    SEC_PKCS7ContentInfo *cinfo;

    cinfo = p7dcx->cinfo;
    if (p7dcx->dcx != NULL) {
	if (SEC_ASN1DecoderFinish (p7dcx->dcx) != SECSuccess) {
	    SEC_PKCS7DestroyContentInfo (cinfo);
	    cinfo = NULL;
	}
    }

    if (p7dcx->worker.decryptobj) {
        sec_PKCS7DestroyDecryptObject (p7dcx->worker.decryptobj);
    }
    PORT_FreeArena (p7dcx->tmp_poolp, PR_FALSE);
    PORT_Free (p7dcx);
    return cinfo;
}
