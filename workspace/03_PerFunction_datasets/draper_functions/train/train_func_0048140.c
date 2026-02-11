AuSetCloseDownMode(
                   AuServer       *aud,
                   int             mode,
                   AuStatus       *ret_status
                   )
{
    auSetCloseDownModeReq *req;

    if (ret_status)
	*ret_status = AuSuccess;

    _AuLockServer();
    _AuGetReq(SetCloseDownMode, req, aud);

    req->mode = mode;

    (void) _AuIfRoundTrip(aud, ret_status);

    _AuUnlockServer();
    _AuSyncHandle(aud);
}
