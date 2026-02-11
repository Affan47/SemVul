GetClientID(Display *dpy, Window window)
{
	char *client_id = NULL;
	Window client_leader = None;
	XTextProperty tp;
	Atom actual_type;
	int actual_format;
	unsigned long nitems;
	unsigned long bytes_after;
	unsigned char *prop = NULL;

	if (!SessionSupport)
	{
		return NULL;
	}

	if (!_XA_WM_CLIENT_LEADER)
	{
		_XA_WM_CLIENT_LEADER = XInternAtom(
			dpy, "WM_CLIENT_LEADER", False);
	}
	if (!_XA_SM_CLIENT_ID)
	{
		_XA_SM_CLIENT_ID = XInternAtom(dpy, "SM_CLIENT_ID", False);
	}

	if (XGetWindowProperty(
		    dpy, window, _XA_WM_CLIENT_LEADER, 0L, 1L, False,
		    AnyPropertyType, &actual_type, &actual_format, &nitems,
		    &bytes_after, &prop) == Success)
	{
		if (actual_type == XA_WINDOW && actual_format == 32 &&
		    nitems == 1 && bytes_after == 0)
		{
			client_leader = (Window)(*(long *)prop);
		}
	}

	if (!client_leader)
	{
		client_leader = window;
	}

	if (client_leader)
	{
		if (XGetTextProperty(dpy, client_leader, &tp, _XA_SM_CLIENT_ID))
		{
			if (tp.encoding == XA_STRING && tp.format == 8 &&
			    tp.nitems != 0)
			{
				client_id = (char *) tp.value;
			}
		}
	}

	if (prop)
	{
		XFree (prop);
	}

	return client_id;
}
