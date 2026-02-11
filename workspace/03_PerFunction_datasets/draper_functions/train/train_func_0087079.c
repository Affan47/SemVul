httpDiscardTransmitData(HttpConn *conn)
{
    HttpTx      *tx;
    HttpQueue   *q, *qhead;

    tx = conn->tx;
    if (tx == 0) {
        return;
    }
    qhead = tx->queue[HTTP_QUEUE_TX];
    for (q = qhead->nextQ; q != qhead; q = q->nextQ) {
        httpDiscardData(q, 1);
    }
}
