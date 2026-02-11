incomingFileData(HttpQueue *q, HttpPacket *packet)
{
    HttpConn    *conn;
    HttpTx      *tx;
    HttpRx      *rx;
    HttpRange   *range;
    MprBuf      *buf;
    MprFile     *file;
    ssize       len;

    conn = q->conn;
    tx = conn->tx;
    rx = conn->rx;
    file = (MprFile*) q->queueData;

    if (file == 0) {

        return;
    }
    if (httpGetPacketLength(packet) == 0) {

        if (file) {
            mprCloseFile(file);
        }
        q->queueData = 0;
        return;
    }
    buf = packet->content;
    len = mprGetBufLength(buf);
    mprAssert(len > 0);

    range = rx->inputRange;
    if (range && mprSeekFile(file, SEEK_SET, range->start) != range->start) {
        httpError(conn, HTTP_CODE_INTERNAL_SERVER_ERROR, "Can't seek to range start to %d", range->start);
    } else {
        if (mprWriteFile(file, mprGetBufStart(buf), len) != len) {
            httpError(conn, HTTP_CODE_INTERNAL_SERVER_ERROR, "Can't PUT to %s", tx->filename);
        }
    }
}
