matchRange(HttpConn *conn, HttpRoute *route, int dir)
{
    mprAssert(conn->rx);

    if ((dir & HTTP_STAGE_TX) && conn->tx->outputRanges) {
        return HTTP_ROUTE_OK;
    }
    return HTTP_ROUTE_REJECT;
}
