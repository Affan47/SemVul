xdestroy(ev, cldata)
XEvent *ev;
XtPointer cldata;
{
    XDestroyWindowEvent *event = (XDestroyWindowEvent *)ev;
    IMConnection *conn = (IMConnection *)cldata;

    TRACE(("imlib:xdestroy()\n"));

    if (event->type != DestroyNotify ||
	event->window != conn->transport.priv.x.client) {
	return;
    }


    IMDispatch(conn, TRANSPORT_ERROR);
}
