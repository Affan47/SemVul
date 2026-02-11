IMUnregisterConnection(conn)
IMConnection *conn;
{
    IMProtocolWidget ipw = (IMProtocolWidget)conn->proto_widget;
    IMConnection *p, *q;

    p = ipw->imp.connection_list;
    q = NULL;
    while (p != NULL) {
	if (p == conn) {
	    if (q == NULL) {
		ipw->imp.connection_list = p->next;
	    } else {
		q->next = p->next;
	    }


	    if (ipw->imp.connection_list == NULL &&
		ipw->imp.no_more_connections == True) {
		DPRINT(("IMProtocolWidget no longer necessary. killing..\n"));
		XtDestroyWidget((Widget)ipw);
	    }
	    return;
	}
	q = p;
	p = p->next;
    }
}
