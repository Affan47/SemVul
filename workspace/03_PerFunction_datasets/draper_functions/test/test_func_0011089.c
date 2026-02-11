parent_window(Window win, char **name) {
#if !NO_X11
	Window r, parent;
	Window *list;
	XErrorHandler old_handler;
	unsigned int nchild;
	int rc;
#endif

	if (name != NULL) {
		*name = NULL;
	}
	RAWFB_RET(None)
#if NO_X11
	nox11_exit(1);
	if (!name || !win) {}
	return None;
#else

	old_handler = XSetErrorHandler(trap_xerror);
	trapped_xerror = 0;
	rc = XQueryTree_wr(dpy, win, &r, &parent, &list, &nchild);
	XSetErrorHandler(old_handler);

	if (! rc || trapped_xerror) {
		trapped_xerror = 0;
		return None;
	}
	trapped_xerror = 0;

	if (list) {
		XFree_wr(list);
	}
	if (parent && name) {
		XFetchName(dpy, parent, name);
	}
	return parent;
#endif
}
