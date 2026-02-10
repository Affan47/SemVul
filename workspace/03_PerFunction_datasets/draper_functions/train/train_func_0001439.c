GetClientID (Window window)


{
    char *client_id = NULL;
    Window client_leader;
    XTextProperty tp;
    Atom actual_type;
    int actual_format;
    unsigned long nitems;
    unsigned long bytes_after;
    unsigned char *prop = NULL;

    if (XGetWindowProperty (dpy, window, _XA_WM_CLIENT_LEADER,
	0L, 1L, False, AnyPropertyType,	&actual_type, &actual_format,
	&nitems, &bytes_after, &prop) == Success)
    {
	if (actual_type == XA_WINDOW && actual_format == 32 &&
	    nitems == 1 && bytes_after == 0)
	{
	    client_leader = *((Window *) prop);

	    if (XGetTextProperty (dpy, client_leader, &tp, _XA_SM_CLIENT_ID))
	    {
		if (tp.encoding == XA_STRING &&
		    tp.format == 8 && tp.nitems != 0)
		    client_id = (char *) tp.value;
	    }
	}

	if (prop)
	    XFree (prop);
    }

    return client_id;
}
