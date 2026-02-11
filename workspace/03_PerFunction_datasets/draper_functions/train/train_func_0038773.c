get_pointer_fvwm_window(void)
{
	int x,y;
	Window win;
	Window ancestor;
	FvwmWindow *t;

	if (FQueryPointer(
		    dpy, Scr.Root, &JunkRoot, &win, &JunkX, &JunkY,
		    &x, &y, &JunkMask) == False)
	{

		return NULL;
	}
	for (t = NULL ; win != Scr.Root && win != None; win = ancestor)
	{
		Window root = None;
		Window *children;
		unsigned int nchildren;

		if (XFindContext(dpy, win, FvwmContext, (caddr_t *) &t) !=
		    XCNOENT)
		{

			return t;
		}

		children = NULL;
		if (!XQueryTree(
			    dpy, win, &root, &ancestor, &children, &nchildren))
		{
			return NULL;
		}
		if (children)
		{
			XFree(children);
		}
	}

	return t;
}
