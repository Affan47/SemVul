lookupCacheControl(HttpConn *conn)
{
    HttpRx      *rx;
    HttpTx      *tx;
    HttpCache   *cache;
    cchar       *mimeType, *ukey;
    int         next;

    rx = conn->rx;
    tx = conn->tx;


    for (next = 0; (cache = mprGetNextItem(rx->route->caching, &next)) != 0; ) {
        if (cache->uris) {
            if (cache->flags & HTTP_CACHE_ONLY) {
                ukey = sfmt("%s?%s", rx->pathInfo, httpGetParamsString(conn));
            } else {
                ukey = rx->pathInfo;
            }
            if (!mprLookupKey(cache->uris, ukey)) {
                continue;
            }
        }
        if (cache->methods && !mprLookupKey(cache->methods, rx->method)) {
            continue;
        }
        if (cache->extensions && !mprLookupKey(cache->extensions, tx->ext)) {
            continue;
        }
        if (cache->types) {
            if ((mimeType = (char*) mprLookupMime(rx->route->mimeTypes, tx->ext)) != 0) {
                if (!mprLookupKey(cache->types, mimeType)) {
                    continue;
                }
            }
        }

        break;
    }
    return cache;
}
