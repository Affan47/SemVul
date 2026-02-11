wm_get_focused(Display *dpy)
{
	Window focused = None, root = None, *children;
	unsigned int tmp_u;
	int revert_to, status, real_format;
	Atom real_type;
	unsigned long items_read, items_left;
	unsigned char *data;

	XGetInputFocus(dpy, &focused, &revert_to);

	while(focused != None && focused != root)
	{
		status = XGetWindowProperty(dpy, focused, XA_WM_STATE,
		                            0L, 1L, False, XA_WM_STATE, &real_type, &real_format,
		                            &items_read, &items_left, &data);
		if(status == Success)
		{
			XFree(data);
			if(items_read)
				break;
		}
		XQueryTree(dpy, focused, &root, &focused, &children, &tmp_u);
		if(children)
			XFree(children);
	}

	return focused;
}
