httpAppendHeaderString(HttpConn *conn, cchar *key, cchar *value)
{
    cchar   *oldValue;

    mprAssert(key && *key);
    mprAssert(value && *value);

    oldValue = mprLookupKey(conn->tx->headers, key);
    if (oldValue) {
        if (scasematch(key, "Set-Cookie")) {
            mprAddDuplicateKey(conn->tx->headers, key, sclone(value));
        } else {
            addHdr(conn, key, sfmt("%s, %s", oldValue, value));
        }
    } else {
        addHdr(conn, key, sclone(value));
    }
}
