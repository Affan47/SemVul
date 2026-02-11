event_to_wire(Display *dpy, XEvent *event, xEvent *wire)
{
    XExtDisplayInfo *info = find_display(dpy);

    SecurityCheckExtension(dpy, info, False);

    switch ((event->type & 0x7F) - info->codes->first_event)
    {
	case XSecurityAuthorizationRevoked:
	{
	    xSecurityAuthorizationRevokedEvent *rwire =
		(xSecurityAuthorizationRevokedEvent *)wire;
	    XSecurityAuthorizationRevokedEvent *revent =
		(XSecurityAuthorizationRevokedEvent *)event;
	    rwire->type = revent->type | (revent->send_event ? 0x80 : 0);
	    rwire->sequenceNumber = revent->serial & 0xFFFF;
	    return True;
	}
    }
    return False;
}
