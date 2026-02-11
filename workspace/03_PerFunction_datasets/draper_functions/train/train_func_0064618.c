ResolvePendingWindows(void)
{
	ProxyWindow *proxy;

	for (proxy=firstProxy; proxy != NULL; proxy=proxy->next)
	{
		if(proxy->pending_config)
		{
			MoveProxiedWindow(proxy,proxy->x,proxy->y,
				proxy->goal_width,proxy->goal_height);
		}
	}
}
