incomingData(HttpQueue *q, HttpPacket *packet)
{
    mprAssert(q);
    mprAssert(packet);
    mprAssert(httpVerifyQueue(q));

    if (q->nextQ->put) {
        httpPutPacketToNext(q, packet);
    } else {


        if (httpGetPacketLength(packet) > 0) {
            httpJoinPacketForService(q, packet, 0);
            HTTP_NOTIFY(q->conn, 0, HTTP_NOTIFY_READABLE);
        } else {

            httpPutForService(q, packet, HTTP_DELAY_SERVICE);
            HTTP_NOTIFY(q->conn, 0, HTTP_NOTIFY_READABLE);
        }
    }
    mprAssert(httpVerifyQueue(q));
}
