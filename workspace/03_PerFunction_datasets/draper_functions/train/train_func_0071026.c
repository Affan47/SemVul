DestroyWindow(Window w)
{
	ProxyWindow *proxy;
	ProxyWindow *prev;

	for (proxy=firstProxy, prev = NULL; proxy != NULL;
		prev = proxy, proxy=proxy->next)
	{
		if (proxy->proxy==w || proxy->window==w)
			break;
	}
	if (proxy == NULL)
	{
		return;
	}
	if (prev == NULL)
	{
		firstProxy = proxy->next;
	}
	else
	{
		prev->next = proxy->next;
	}
	if (selectProxy == proxy)
	{
		selectProxy = NULL;
	}
	if (enterProxy == proxy)
	{
		enterProxy = NULL;
	}
	if(!proxy->flags.is_iconified)
	{
		IsolateCheck(proxy,1);
	}
	CloseOneWindow(proxy);
	delete_ProxyWindow(proxy);

	return;
}
