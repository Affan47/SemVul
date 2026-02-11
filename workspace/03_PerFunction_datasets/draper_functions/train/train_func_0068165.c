espGetSession(HttpConn *conn, int create)
{
    EspReq      *req;
    char        *id;

    mprAssert(conn);
    req = conn->data;
    mprAssert(req);
    if (req->session || !conn) {
        return req->session;
    }
    id = espGetSessionID(conn);
    if (id || create) {
        req->session = espAllocSession(conn, id, conn->limits->sessionTimeout);
        if (req->session && !id) {
            httpSetCookie(conn, ESP_SESSION, req->session->id, "/", NULL, 0, conn->secure);
        }
    }
    return req->session;
}
