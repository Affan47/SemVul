DXLCheckPacket(DXLConnection *conn, DXLPacketTypeEnum type, int requestId,
                DXLEvent *event, DXLPacketPredicate pp, const void *arg)
{
    DXLEvent *e;

    e = DXLFindEventInList(conn,conn->events,type,requestId, pp, arg);
    if (e) {
        DXLCopyEvent(event, e);
        return 1;
    }
    return 0;
}
