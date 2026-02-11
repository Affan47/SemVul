addParamsFromQueue(HttpQueue *q)
{
    HttpConn    *conn;
    HttpRx      *rx;
    MprBuf      *content;

    mprAssert(q);

    conn = q->conn;
    rx = conn->rx;

    if ((rx->form || rx->upload) && q->first && q->first->content) {
        httpJoinPackets(q, -1);
        content = q->first->content;
        mprAddNullToBuf(content);
        mprLog(6, "Form body data: length %d, \"%s\"", mprGetBufLength(content), mprGetBufStart(content));
        addParamsFromBuf(conn, mprGetBufStart(content), mprGetBufLength(content));
    }
}
