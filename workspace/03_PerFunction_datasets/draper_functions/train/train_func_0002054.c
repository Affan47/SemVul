ReceiveData(SSL* ssl, byte* output, int sz)
{
    int size;

    CYASSL_ENTER("ReceiveData()");

    if (ssl->error == WANT_READ)
        ssl->error = 0;

    if (ssl->options.handShakeState != HANDSHAKE_DONE) {
        int err;
        CYASSL_MSG("Handshake not complete, trying to finish");
        if ( (err = CyaSSL_negotiate(ssl)) != 0)
            return  err;
    }

    while (ssl->buffers.clearOutputBuffer.length == 0)
        if ( (ssl->error = ProcessReply(ssl)) < 0) {
            CYASSL_ERROR(ssl->error);
            if (ssl->error == ZERO_RETURN) {
                CYASSL_MSG("Zero return, no more data coming");
                ssl->options.isClosed = 1;
                return 0;
            }
            if (ssl->error == SOCKET_ERROR_E) {
                if (ssl->options.connReset || ssl->options.isClosed) {
                    CYASSL_MSG("Peer reset or closed, connection done");
                    return 0;
                }
            }
            return ssl->error;
        }

    if (sz < (int)ssl->buffers.clearOutputBuffer.length)
        size = sz;
    else
        size = ssl->buffers.clearOutputBuffer.length;

    XMEMCPY(output, ssl->buffers.clearOutputBuffer.buffer, size);
    ssl->buffers.clearOutputBuffer.length -= size;
    ssl->buffers.clearOutputBuffer.buffer += size;

    if (ssl->buffers.clearOutputBuffer.length == 0 &&
                                           ssl->buffers.inputBuffer.dynamicFlag)
       ShrinkInputBuffer(ssl, NO_FORCED_FREE);

    CYASSL_LEAVE("ReceiveData()", size);
    return size;
}
