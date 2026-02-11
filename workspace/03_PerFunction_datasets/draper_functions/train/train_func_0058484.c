FetchWmColormapWindows (FvwmWindow *fw)
{
	XWindowAttributes getattribs;
	XSetWindowAttributes setattribs;
	long i;
	unsigned long valuemask;

	if (fw->cmap_windows != (Window *)NULL)
	{
		XFree((void *)fw->cmap_windows);
	}

	if (!XGetWMColormapWindows (dpy, FW_W(fw), &(fw->cmap_windows),
				   &(fw->number_cmap_windows)))
	{
		fw->number_cmap_windows = 0;
		fw->cmap_windows = NULL;
	}


	if (fw->number_cmap_windows != 0)
	{
		for (i = 0; i < fw->number_cmap_windows; i++)
		{
			if (XGetWindowAttributes(
				    dpy, fw->cmap_windows[i], &getattribs))
			{
				valuemask = CWEventMask;
				setattribs.event_mask =
					getattribs.your_event_mask |
					EnterWindowMask | LeaveWindowMask;
				XChangeWindowAttributes(
					dpy, fw->cmap_windows[i], valuemask,
					&setattribs);
			}
		}
	}
	return;
}
