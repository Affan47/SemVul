getToplevelWindow(dpy, win, wm_state)
Display *dpy;
Window win;
Atom wm_state;
{
    Atom type;
    int format;
    unsigned long nitems, bytesafter;
    unsigned char *data;
    Window root, parent;
    Window *children;
    unsigned int nchildren;


    for (;;) {
	type = None;
	if (wm_state != None) {
	    data = NULL;
	    XGetWindowProperty(dpy, win, wm_state, 0L, 0L, False,
			       AnyPropertyType, &type, &format,
			       &nitems, &bytesafter, &data);
	    if (data != NULL) XtFree((char *)data);
	    if (type != None) break;
	}
	if (!XQueryTree(dpy, win, &root, &parent, &children, &nchildren)) break;
	if (nchildren > 0) XtFree((char *)children);
	if (root == parent) break;
	win = parent;
    }
    return win;
}
