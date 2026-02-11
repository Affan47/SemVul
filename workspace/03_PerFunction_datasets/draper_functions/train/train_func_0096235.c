DPMSGetTimeouts(Display *dpy, CARD16 *standby, CARD16 *suspend, CARD16 *off)
{
    XExtDisplayInfo *info = find_display (dpy);
    register xDPMSGetTimeoutsReq *req;
    xDPMSGetTimeoutsReply rep;

    DPMSCheckExtension (dpy, info, 0);

    LockDisplay(dpy);
    GetReq(DPMSGetTimeouts, req);
    req->reqType = info->codes->major_opcode;
    req->dpmsReqType = X_DPMSGetTimeouts;

    if (!_XReply(dpy, (xReply *)&rep, 0, xTrue)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return False;
    }
    UnlockDisplay(dpy);
    SyncHandle();
    *standby = rep.standby;
    *suspend = rep.suspend;
    *off = rep.off;
    return 1;
}
