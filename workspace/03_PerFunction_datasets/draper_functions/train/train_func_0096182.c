XagQueryApplicationGroup(
    Display* dpy,
    XID resource,
    XAppGroup* app_group_return)
{
    XExtDisplayInfo *info = find_display (dpy);
    xXagQueryReq *req;
    xXagQueryReply rep;

    XagCheckExtension (dpy, info, False);

    LockDisplay(dpy);
    GetReq(XagQuery, req);
    req->reqType = info->codes->major_opcode;
    req->xagReqType = X_XagQuery;
    req->resource = resource;
    if (!_XReply(dpy, (xReply *)&rep, 0, xFalse)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return False;
    }
    *app_group_return = rep.app_group;
    UnlockDisplay(dpy);
    SyncHandle();
    return True;

}
