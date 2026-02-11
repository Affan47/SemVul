FillBuf(Stream *sPtr)
{

    int n      = NsOpenSSLConnOp(sPtr->sslconn->ssl, sPtr->buf, BUFSIZE, NSOPENSSL_RECV);
    int status = NS_TRUE;

    if (n > 0) {
        sPtr->buf[n] = '\0';
        sPtr->ptr    = sPtr->buf;
        sPtr->cnt    = n;
    } else if (n == 0) {
        status       = NS_FALSE;
    } else {
        Ns_Log(Error, "FillBuf: failed to fill socket stream buffer");
        sPtr->error  = 1;
        status       = NS_FALSE;
    }

    return status;
}
