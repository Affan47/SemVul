processParsed(HttpConn *conn)
{
    HttpRx      *rx;

    rx = conn->rx;
    if (!rx->form && conn->endpoint) {


        routeRequest(conn);
    }
    if (rx->streamInput) {
        httpStartPipeline(conn);
    }
    httpSetState(conn, HTTP_STATE_CONTENT);
    if (conn->workerEvent && conn->tx->started && rx->eof) {
        httpSetState(conn, HTTP_STATE_RUNNING);
        return 0;
    }
    return 1;
}
