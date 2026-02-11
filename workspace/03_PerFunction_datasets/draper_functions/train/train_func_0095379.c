RecalcProxyTweaks(void)
{
	ProxyWindow *proxy;
	for (proxy=firstProxy; proxy != NULL; proxy=proxy->next)
	{
		proxy->tweakx=proxy->proxyx -
			(proxy->x + (proxy->w-proxy->proxyw)/2);
		proxy->tweaky=proxy->proxyy -
			(proxy->y + (proxy->h-proxy->proxyh)/2);
	}
}
