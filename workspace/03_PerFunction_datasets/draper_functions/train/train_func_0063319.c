httpCreateQueue(HttpConn *conn, HttpStage *stage, int dir, HttpQueue *prev)
{
    HttpQueue   *q;

    if ((q = mprAllocObj(HttpQueue, manageQueue)) == 0) {
        return 0;
    }
    q->conn = conn;
    httpInitQueue(conn, q, stage->name);
    httpInitSchedulerQueue(q);
    httpAssignQueue(q, stage, dir);
    if (prev) {
        httpInsertQueue(prev, q);
    }
    return q;
}
