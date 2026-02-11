httpContentNotModified(HttpConn *conn)
{
    HttpRx      *rx;
    HttpTx      *tx;
    MprTime     modified;
    bool        same;

    rx = conn->rx;
    tx = conn->tx;

    if (rx->flags & HTTP_IF_MODIFIED) {


        mprAssert(tx->fileInfo.valid);
        modified = (MprTime) tx->fileInfo.mtime * MPR_TICKS_PER_SEC;
        same = httpMatchModified(conn, modified) && httpMatchEtag(conn, tx->etag);
        if (tx->outputRanges && !same) {
            tx->outputRanges = 0;
        }
        return same;
    }
    return 0;
}
