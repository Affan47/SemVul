GetClientCoordinates(ccw)
ConversionControlWidget ccw;
{
    Display *dpy = XtDisplay(ccw);
    Window root = RootWindowOfScreen(XtScreen(ccw));
    Window win = ccw->ccontrol.clientwindow;
    Window junk;
    int rootx, rooty;

    if (!XTranslateCoordinates(dpy, win, root, 0, 0, &rootx, &rooty, &junk)) {
	WidgetWarning((Widget)ccw, "windowError", "differentRoot",
		      "clientWindow and conversion widget have different root. this should not happen!");
	rootx = rooty = 0;
    }

    ccw->ccontrol.client_rootx = rootx;
    ccw->ccontrol.client_rooty = rooty;
}
