wire_to_event(Display *dpy, XEvent *event, xEvent *wire)
{
    XExtDisplayInfo *info = find_display(dpy);

    SecurityCheckExtension (dpy, info, False);

    switch ((wire->u.u.type & 0x7F) - info->codes->first_event)
    {
	case XSecurityAuthorizationRevoked:
	{
	    xSecurityAuthorizationRevokedEvent *rwire =
		(xSecurityAuthorizationRevokedEvent *)wire;
	    XSecurityAuthorizationRevokedEvent *revent =
		(XSecurityAuthorizationRevokedEvent *)event;

	  revent->type = rwire->type & 0x7F;
	  revent->serial = _XSetLastRequestRead(dpy,
						(xGenericReply *) wire);
	  revent->send_event = (rwire->type & 0x80) != 0;
	  revent->display = dpy;
	  revent->auth_id = rwire->authId;
	  return True;
	}
    }
    return False;
}
