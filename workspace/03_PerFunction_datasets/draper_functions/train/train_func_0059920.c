GrowInputBuffer(SSL* ssl, int size, int usedLength)
{
    byte* tmp = (byte*) XMALLOC(size + usedLength, ssl->heap,
                                DYNAMIC_TYPE_IN_BUFFER);
    CYASSL_MSG("growing input buffer\n");

    if (!tmp) return MEMORY_E;

    if (usedLength)
        XMEMCPY(tmp, ssl->buffers.inputBuffer.buffer +
                    ssl->buffers.inputBuffer.idx, usedLength);

    if (ssl->buffers.inputBuffer.dynamicFlag)
        XFREE(ssl->buffers.inputBuffer.buffer,ssl->heap,DYNAMIC_TYPE_IN_BUFFER);

    ssl->buffers.inputBuffer.dynamicFlag = 1;
    ssl->buffers.inputBuffer.buffer = tmp;
    ssl->buffers.inputBuffer.bufferSize = size + usedLength;
    ssl->buffers.inputBuffer.idx    = 0;
    ssl->buffers.inputBuffer.length = usedLength;

    return 0;
}
