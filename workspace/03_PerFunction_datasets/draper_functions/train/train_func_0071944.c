GetRegProp(dpy, regPropp, numItemsp, domsg)
    Display	*dpy;
    char_u	**regPropp;
    long_u	*numItemsp;
    int		domsg;
{
    int		result, actualFormat;
    long_u	bytesAfter;
    Atom	actualType;
    XErrorHandler old_handler;

    *regPropp = NULL;
    old_handler = XSetErrorHandler(x_error_check);
    got_x_error = FALSE;

    result = XGetWindowProperty(dpy, RootWindow(dpy, 0), registryProperty, 0L,
				(long)MAX_PROP_WORDS, False,
				XA_STRING, &actualType,
				&actualFormat, numItemsp, &bytesAfter,
				regPropp);

    XSync(dpy, FALSE);
    (void)XSetErrorHandler(old_handler);
    if (got_x_error)
	return FAIL;

    if (actualType == None)
    {

	*numItemsp = 0;
	*regPropp = empty_prop;
	return OK;
    }


    if (result != Success || actualFormat != 8 || actualType != XA_STRING)
    {
	if (*regPropp != NULL)
	    XFree(*regPropp);
	XDeleteProperty(dpy, RootWindow(dpy, 0), registryProperty);
	if (domsg)
	    EMSG(_("E251: VIM instance registry property is badly formed.  Deleted!"));
	return FAIL;
    }
    return OK;
}
