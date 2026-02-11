XShapeQueryExtents (
    register Display *dpy,
    Window window,
    int *bShaped, int *xbs, int *ybs, unsigned int *wbs, unsigned int *hbs,
    int *cShaped, int *xcs, int *ycs, unsigned int *wcs, unsigned int *hcs )
{
    XExtDisplayInfo *info = find_display (dpy);
    xShapeQueryExtentsReply	    rep;
    register xShapeQueryExtentsReq *req;

    ShapeCheckExtension (dpy, info, 0);

    LockDisplay (dpy);
    GetReq (ShapeQueryExtents, req);
    req->reqType = info->codes->major_opcode;
    req->shapeReqType = X_ShapeQueryExtents;
    req->window = window;
    if (!_XReply (dpy, (xReply *) &rep, 0, xTrue)) {
	UnlockDisplay (dpy);
	SyncHandle ();
	return 0;
    }
    *bShaped = rep.boundingShaped;
    *cShaped = rep.clipShaped;
    *xbs = cvtINT16toInt (rep.xBoundingShape);
    *ybs = cvtINT16toInt (rep.yBoundingShape);
    *wbs = rep.widthBoundingShape;
    *hbs = rep.heightBoundingShape;
    *xcs = cvtINT16toInt (rep.xClipShape);
    *ycs = cvtINT16toInt (rep.yClipShape);
    *wcs = rep.widthClipShape;
    *hcs = rep.heightClipShape;
    UnlockDisplay (dpy);
    SyncHandle ();
    return 1;
}
