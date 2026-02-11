mprGetBlockFromBuf(MprBuf *bp, char *buf, ssize size)
{
    ssize     thisLen, bytesRead;

    mprAssert(buf);
    mprAssert(size >= 0);
    mprAssert(bp->buflen == (bp->endbuf - bp->data));


    bytesRead = 0;
    while (size > 0) {
        thisLen = mprGetBufLength(bp);
        thisLen = min(thisLen, size);
        if (thisLen <= 0) {
            break;
        }

        memcpy(buf, bp->start, thisLen);
        buf += thisLen;
        bp->start += thisLen;
        size -= thisLen;
        bytesRead += thisLen;
    }
    return bytesRead;
}
