UninstallRootColormapQScanner(Display *dpy, XEvent *ev, char *args)
{
    if (!*args) {
	if (ev->type == EnterNotify) {
	    if (ev->xcrossing.mode != NotifyGrab)
		*args = 1;
	} else if (ev->type == LeaveNotify) {
	    if (ev->xcrossing.mode == NotifyNormal)
		*args = 1;
	}
    }

    return (False);
}
