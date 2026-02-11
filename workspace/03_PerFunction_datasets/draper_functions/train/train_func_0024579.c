processDir(HttpQueue *q)
{
    HttpConn        *conn;
    HttpTx          *tx;
    HttpRx          *rx;
    MprList         *list;
    MprDirEntry     *dp;
    Dir             *dir;
    uint            nameSize;
    int             next;

    conn = q->conn;
    rx = conn->rx;
    tx = conn->tx;
    dir = conn->data;

    mprLog(5, "processDir");
    mprAssert(tx->filename);

    httpSetHeaderString(conn, "Cache-Control", "no-cache");
    httpSetHeaderString(conn, "Last-Modified", conn->http->currentDate);
    parseQuery(conn);

    list = mprGetPathFiles(tx->filename, 1);
    if (list == 0) {
        httpWrite(q, "<h2>Can't get file list</h2>\r\n");
        outputFooter(q);
        return;
    }
    if (dir->pattern) {
        filterDirList(conn, list);
    }
    sortList(conn, list);


    nameSize = 0;
    for (next = 0; (dp = mprGetNextItem(list, &next)) != 0; ) {
        nameSize = max((int) strlen(dp->name), nameSize);
    }
    nameSize = max(nameSize, 22);

    outputHeader(q, rx->pathInfo, nameSize);
    for (next = 0; (dp = mprGetNextItem(list, &next)) != 0; ) {
        outputLine(q, dp, tx->filename, nameSize);
    }
    outputFooter(q);
    httpFinalize(conn);
}
