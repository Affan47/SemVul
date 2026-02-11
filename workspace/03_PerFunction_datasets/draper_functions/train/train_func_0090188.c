espShowRequest(HttpConn *conn)
{
    MprHash     *env;
    MprKey      *kp;
    MprBuf      *buf;
    HttpRx      *rx;
    HttpQueue   *q;
    cchar       *query;
    char        qbuf[MPR_MAX_STRING], **keys, *value;
    int         i, numKeys;

    rx = conn->rx;
    httpSetHeaderString(conn, "Cache-Control", "no-cache");
    httpCreateCGIParams(conn);
    espRender(conn, "\r\n");


    if ((query = espGetQueryString(conn)) != 0) {
        scopy(qbuf, sizeof(qbuf), query);
        if ((numKeys = getParams(&keys, qbuf, (int) strlen(qbuf))) > 0) {
            for (i = 0; i < (numKeys * 2); i += 2) {
                value = keys[i+1];
                espRender(conn, "QUERY %s=%s\r\n", keys[i], value ? value: "null");
            }
        }
        espRender(conn, "\r\n");
    }


    env = espGetHeaderHash(conn);
    for (ITERATE_KEYS(env, kp)) {
        espRender(conn, "HEADER %s=%s\r\n", kp->key, kp->data ? kp->data: "null");
    }
    espRender(conn, "\r\n");


    for (ITERATE_KEYS(conn->rx->svars, kp)) {
        espRender(conn, "SERVER %s=%s\r\n", kp->key, kp->data ? kp->data: "null");
    }
    espRender(conn, "\r\n");


    if ((env = espGetParams(conn)) != 0) {
        for (ITERATE_KEYS(env, kp)) {
            espRender(conn, "FORM %s=%s\r\n", kp->key, kp->data ? kp->data: "null");
        }
        espRender(conn, "\r\n");
    }


    q = conn->readq;
    if (q->first && rx->bytesRead > 0 && scmp(rx->mimeType, "application/x-www-form-urlencoded") == 0) {
        buf = q->first->content;
        mprAddNullToBuf(buf);
        if ((numKeys = getParams(&keys, mprGetBufStart(buf), (int) mprGetBufLength(buf))) > 0) {
            for (i = 0; i < (numKeys * 2); i += 2) {
                value = keys[i+1];
                espRender(conn, "BODY %s=%s\r\n", keys[i], value ? value: "null");
            }
        }
        espRender(conn, "\r\n");
    }
}
