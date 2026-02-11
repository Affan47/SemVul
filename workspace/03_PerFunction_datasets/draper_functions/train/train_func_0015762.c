sec_pkcs7_decoder_finish_decrypt (SEC_PKCS7DecoderContext *p7dcx,
				  PLArenaPool *poolp,
				  SEC_PKCS7EncryptedContentInfo *enccinfo)
{
    struct sec_pkcs7_decoder_worker *worker;


    worker = &(p7dcx->worker);


    if (worker->decryptobj == NULL)
	return SECSuccess;


    SEC_ASN1DecoderClearFilterProc (p7dcx->dcx);


    sec_pkcs7_decoder_work_data (p7dcx, worker, NULL, 0, PR_TRUE);


    sec_PKCS7DestroyDecryptObject (worker->decryptobj);
    worker->decryptobj = NULL;

    return SECSuccess;
}
