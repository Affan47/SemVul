XShmAttach(Display *dpy, XShmSegmentInfo *shminfo)
{
    XExtDisplayInfo *info = find_display (dpy);
    register xShmAttachReq *req;

    ShmCheckExtension (dpy, info, 0);

    LockDisplay(dpy);
    GetReq(ShmAttach, req);
    req->reqType = info->codes->major_opcode;
    req->shmReqType = X_ShmAttach;
    req->shmseg = shminfo->shmseg = XAllocID(dpy);
    req->shmid = shminfo->shmid;
    req->readOnly = shminfo->readOnly ? xTrue : xFalse;
    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
}
