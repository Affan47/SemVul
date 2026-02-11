setDesktopGeometry(int , const NETSize &geometry) {

#ifdef    NETWMDEBUG
    fprintf(stderr, "NETRootInfo::setDesktopGeometry( -- , { %d, %d }) (%s)\n",
	    geometry.width, geometry.height, (p->role == WindowManager) ? "WM" : "Client");
#endif

    if (p->role == WindowManager) {
	p->geometry = geometry;

	long data[2];
	data[0] = p->geometry.width;
	data[1] = p->geometry.height;

	XChangeProperty(p->display, p->root, net_desktop_geometry, XA_CARDINAL, 32,
			PropModeReplace, (unsigned char *) data, 2);
    } else {
	XEvent e;

	e.xclient.type = ClientMessage;
	e.xclient.message_type = net_desktop_geometry;
	e.xclient.display = p->display;
	e.xclient.window = p->root;
	e.xclient.format = 32;
	e.xclient.data.l[0] = geometry.width;
	e.xclient.data.l[1] = geometry.height;
	e.xclient.data.l[2] = 0l;
	e.xclient.data.l[3] = 0l;
	e.xclient.data.l[4] = 0l;

	XSendEvent(p->display, p->root, False, netwm_sendevent_mask, &e);
    }
}
