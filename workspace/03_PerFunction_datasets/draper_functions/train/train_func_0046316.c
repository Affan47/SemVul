XagGetApplicationGroupAttributes(Display* dpy, XAppGroup app_group, ...)
{
    va_list var;
    XExtDisplayInfo *info = find_display (dpy);
    xXagGetAttrReq *req;
    xXagGetAttrReply rep;
    int attr;

    XagCheckExtension (dpy, info, False);

    LockDisplay(dpy);
    GetReq(XagGetAttr, req);
    req->reqType = info->codes->major_opcode;
    req->xagReqType = X_XagGetAttr;
    req->app_group = app_group;
    if (!_XReply(dpy, (xReply *)&rep, 0, xFalse)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return False;
    }
    va_start (var, app_group);
    for (attr = va_arg(var, int); attr != 0; attr = va_arg(var, int)) {
	void* ptr;

	switch (attr) {
	case XagNappGroupLeader:
	    ptr = va_arg(var, void*);
	    *(Bool*)ptr = rep.app_group_leader;
	    break;
	case XagNsingleScreen:
	    ptr = va_arg(var, void*);
	    *(Bool*)ptr = rep.single_screen;
	    break;
	case XagNdefaultRoot:
	    ptr = va_arg(var, void*);
	    *(Window*)ptr = rep.default_root;
	    break;
	case XagNrootVisual:
	    ptr = va_arg(var, void*);
	    *(VisualID*)ptr = rep.root_visual;
	    break;
	case XagNdefaultColormap:
	    ptr = va_arg(var, void*);
	    *(Colormap*)ptr = rep.default_colormap;
	    break;
	case XagNblackPixel:
	    ptr = va_arg(var, void*);
	    *(unsigned long*)ptr = rep.black_pixel;
	    break;
	case XagNwhitePixel:
	    ptr = va_arg(var, void*);
	    *(unsigned long*)ptr = rep.white_pixel;
	    break;
	}
    }
    va_end (var);
    UnlockDisplay(dpy);
    SyncHandle();
    return True;
}
