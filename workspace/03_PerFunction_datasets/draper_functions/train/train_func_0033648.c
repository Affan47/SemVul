mprPutFileString(MprFile *file, cchar *str)
{
    MprBuf  *bp;
    ssize   total, bytes, count;
    char    *buf;

    mprAssert(file);
    count = slen(str);


    if (file->buf == 0) {
        file->buf = mprCreateBuf(MPR_BUFSIZE, 0);
        if (file->buf == 0) {
            return MPR_ERR_CANT_ALLOCATE;
        }
    }
    bp = file->buf;

    if (mprGetBufLength(bp) > 0 && mprGetBufSpace(bp) < count) {
        mprFlushFile(file);
    }
    total = 0;
    buf = (char*) str;

    while (count > 0) {
        bytes = mprPutBlockToBuf(bp, buf, count);
        if (bytes < 0) {
            return MPR_ERR_CANT_ALLOCATE;

        } else if (bytes == 0) {
            if (mprFlushFile(file) < 0) {
                return MPR_ERR_CANT_WRITE;
            }
            continue;
        }
        count -= bytes;
        buf += bytes;
        total += bytes;
        file->pos += (MprOff) bytes;
    }
    return total;
}
