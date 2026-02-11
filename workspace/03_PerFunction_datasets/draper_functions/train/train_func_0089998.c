IMXConnection(protocol, xev)
Widget protocol;
XEvent *xev;
{
    XClientMessageEvent *event = (XClientMessageEvent *)xev;
    XClientMessageEvent repl;
    Display *dpy = XtDisplay(protocol);
    Window client_window;
    IMConnection *conn;
    XAEHandle h;

    TRACE(("IMXConnection()\n"));

    if (event->type != ClientMessage ||
	event->display != dpy ||
	event->window != XtWindow(protocol) ||
	event->message_type != IMXConnectAtom(protocol) ||
	event->format != 32) {
	TRACE(("\tinvalid event\n"));
#ifdef DEBUG
	if (event->type != ClientMessage) printf("not ClientMessage\n");
	if (event->display != dpy) printf("wrong display\n");
	if (event->window != XtWindow(protocol)) printf("wrong window\n");
	if (event->message_type != IMXConnectAtom(protocol)) {
	    printf("wrong message type (%ld should be %ld)\n",
		   event->message_type, IMXConnectAtom(protocol));
	}
	if (event->format != 32) printf("wrong format\n");
#endif
	return NULL;
    }
    client_window = event->data.l[0];
    if (!IMValidateWindow(dpy, client_window, (IMWindowProfile *)NULL)) {
	DPRINT(("client window %08lx does not exist\n", client_window));
	return NULL;
    }
    conn = newConnection(protocol);
    conn->transport.ops = &XTransportOps;
    conn->transport.priv.x.client = client_window;
    conn->transport.priv.x.server = communicationWindow(protocol);
    DDPRINT(2, ("new connection #%d: transport=X client=%08lx\n",
		conn->serial, client_window));
    TRACE(("\ttransport version: %ld.%ld\n",
	   event->data.l[1], event->data.l[2]));

    repl.type = ClientMessage;
    repl.window = client_window;
    repl.message_type = IMXConnectAtom(protocol);
    repl.format = 32;
    repl.data.l[0] = conn->transport.priv.x.server;
    repl.data.l[1] = ServerMajorTransportVersion;
    repl.data.l[2] = ServerMinorTransportVersion;
    repl.data.l[3] = XTransportDividingSize;

    h = XAESetIgnoreErrors(dpy);
    XSendEvent(dpy, client_window, False, NoEventMask, (XEvent *)&repl);
    MyAddEventHandler(dpy, client_window, DestroyNotify, StructureNotifyMask,
		      xdestroy, (XtPointer)conn);
    XAEUnset(h);

    MyAddEventHandler(dpy, conn->transport.priv.x.server,
		      ClientMessage, NoEventMask, xinput, (XtPointer)conn);

    return conn;
}
