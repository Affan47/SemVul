xFlush(conn)
IMConnection *conn;
{
    IMBuffer *ibp = IM_OUTBUF(conn);
    XClientMessageEvent repl;
    Widget w = conn->proto_widget;
    Window client_win = conn->transport.priv.x.client;
    Display *dpy = XtDisplay(w);
    int length;
    XAEHandle handle;

    if ((length = IMBUFLEN(ibp)) == 0) return TRANSPORT_OK;

    repl.type = ClientMessage;
    repl.window = client_win;

    handle = XAESet(dpy, xBrokenPipe, (void (*)())NULL, (XPointer)w);

    if (IMBUFLEN(ibp) < XTransportDividingSize) {
	char *data = IMBUFDATA(ibp);

	repl.format = 8;
	repl.message_type = IMMoreDataAtom(w);
	while (length > 20) {
	    bcopy(data, repl.data.b, 20);
	    XSendEvent(dpy, client_win, False, NoEventMask, (XEvent *)&repl);
	    data += 20;
	    length -= 20;
	}
	repl.message_type = IMProtocolAtom(w);
	bzero(repl.data.b, 20);
	bcopy(data, repl.data.b, length);
	XSendEvent(dpy, client_win, False, NoEventMask, (XEvent *)&repl);
    } else {
	repl.format = 32;
	repl.message_type = IMProtocolAtom(w);
	repl.data.l[0] = length;
	repl.data.l[1] = IMKi2CommAtom(w);
	XChangeProperty(dpy, client_win, IMKi2CommAtom(w), XA_STRING,
			8, PropModeAppend,
			(unsigned char *)IMBUFDATA(ibp), IMBUFLEN(ibp));
	XSendEvent(dpy, client_win, False, NoEventMask, (XEvent *)&repl);
    }

    XFlush(dpy);
    XAEUnset(handle);

    IMBufClear(ibp);
    return TRANSPORT_OK;
}
