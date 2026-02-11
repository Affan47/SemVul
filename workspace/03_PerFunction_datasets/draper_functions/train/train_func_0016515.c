mapMethod(HttpConn *conn)
{
    HttpRx      *rx;
    cchar       *method;

    rx = conn->rx;
    if (rx->flags & HTTP_POST) {
        if ((method = httpGetParam(conn, "-http-method-", 0)) != 0) {
            if (!scasematch(method, rx->method)) {
                mprLog(3, "Change method from %s to %s for %s", rx->method, method, rx->uri);
                httpSetMethod(conn, method);
            }
        }
    }
}
