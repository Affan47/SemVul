outgoingCacheFilterService(HttpQueue *q)
{
    HttpPacket  *packet, *data;
    HttpConn    *conn;
    HttpTx      *tx;
    MprKey      *kp;
    cchar       *cachedData;
    ssize       size;
    int         foundDataPacket;

    conn = q->conn;
    tx = conn->tx;
    foundDataPacket = 0;
    cachedData = 0;

    if (tx->status < 200 || tx->status > 299) {
        tx->cacheBuffer = 0;
    }


    if (mprLookupKey(conn->tx->headers, "X-SendCache") != 0) {
        if (fetchCachedResponse(conn)) {
            mprLog(3, "cacheFilter: write cached content for '%s'", conn->rx->uri);
            cachedData = setHeadersFromCache(conn, tx->cachedContent);
            tx->length = slen(cachedData);
        }
    }
    for (packet = httpGetPacket(q); packet; packet = httpGetPacket(q)) {
        if (!httpWillNextQueueAcceptPacket(q, packet)) {
            httpPutBackPacket(q, packet);
            return;
        }
        if (packet->flags & HTTP_PACKET_HEADER) {
            if (!cachedData && tx->cacheBuffer) {


                mprPutFmtToBuf(tx->cacheBuffer, "X-Status: %d\n", tx->status);
                for (kp = 0; (kp = mprGetNextKey(tx->headers, kp)) != 0; ) {
                    mprPutFmtToBuf(tx->cacheBuffer, "%s: %s\n", kp->key, kp->data);
                }
                mprPutCharToBuf(tx->cacheBuffer, '\n');
            }

        } else if (packet->flags & HTTP_PACKET_DATA) {
            if (cachedData) {


                mprFlushBuf(packet->content);
                mprPutBlockToBuf(packet->content, cachedData, (ssize) tx->length);

            } else if (tx->cacheBuffer) {


                size = mprGetBufLength(packet->content);
                if ((tx->cacheBufferLength + size) < conn->limits->cacheItemSize) {
                    mprPutBlockToBuf(tx->cacheBuffer, mprGetBufStart(packet->content), mprGetBufLength(packet->content));
                    tx->cacheBufferLength += size;
                } else {
                    tx->cacheBuffer = 0;
                    mprLog(3, "cacheFilter: Item too big to cache %d bytes, limit %d", tx->cacheBufferLength + size,
                        conn->limits->cacheItemSize);
                }
            }
            foundDataPacket = 1;

        } else if (packet->flags & HTTP_PACKET_END) {
            if (cachedData && !foundDataPacket) {


                data = httpCreateDataPacket((ssize) tx->length);
                mprPutBlockToBuf(data->content, cachedData, (ssize) tx->length);
                httpPutPacketToNext(q, data);

            } else if (tx->cacheBuffer) {


                saveCachedResponse(conn);
            }
        }
        httpPutPacketToNext(q, packet);
    }
}
