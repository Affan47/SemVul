_AuWriteElement(
                AuServer       *aud,
                AuFlowID        flow,
                int             element_num,
                int             state,
                AuUint32   num_bytes,
                AuPointer       data,
                AuStatus       *ret_status
                )
{
    auWriteElementReq *req;

    _AuLockServer();
    _AuGetReq(WriteElement, req, aud);

#undef xfer
#define xfer(x) req->x = x

    xfer(flow);
    xfer(element_num);
    xfer(num_bytes);
    xfer(state);

    req->length += PAD4(num_bytes) >> 2;

    _AuData(aud, data, num_bytes);

    (void) _AuIfRoundTrip(aud, ret_status);
    _AuUnlockServer();
    _AuSyncHandle(aud);
}
