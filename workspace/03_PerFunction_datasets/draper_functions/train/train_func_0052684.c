CloseOneWindow(ProxyWindow *proxy)
{
	if (proxy == NULL)
	{
		return;
	}
	if (proxy->flags.is_shown)
	{
		XUnmapWindow(dpy, proxy->proxy);
		proxy->flags.is_shown = 0;
	}

	return;
}
