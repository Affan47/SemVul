createDigestNonce(HttpConn *conn, cchar *secret, cchar *realm)
{
    MprTime      now;
    char         nonce[256];
    static int64 next = 0;

    mprAssert(realm && *realm);

    now = conn->http->now;
    mprSprintf(nonce, sizeof(nonce), "%s:%s:%Lx:%Lx", secret, realm, now, next++);
    return mprEncode64(nonce);
}
