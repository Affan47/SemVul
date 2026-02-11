httpRemoveConn(Http *http, HttpConn *conn)
{
    lock(http);
    mprRemoveItem(http->connections, conn);
    unlock(http);
}
