p12u_DigestClose(void *arg, PRBool removeFile)
{
    SEC_PKCS12DecoderContext* p12cxt = arg;

    PR_ASSERT(p12cxt);
    if (!p12cxt) {
        return SECFailure;
    }
    p12cxt->currentpos = 0;

    if (PR_TRUE == removeFile) {
        PR_ASSERT(p12cxt->buffer);
        if (!p12cxt->buffer) {
            return SECFailure;
        }
        if (p12cxt->buffer) {
            PORT_Free(p12cxt->buffer);
            p12cxt->buffer = NULL;
            p12cxt->allocated = 0;
            p12cxt->filesize = 0;
        }
    }

    return SECSuccess;
}
