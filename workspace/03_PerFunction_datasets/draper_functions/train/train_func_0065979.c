DrawProxy(ProxyWindow *proxy)
{
	if (proxy)
	{
		DrawWindow(
			proxy, proxy->proxyx, proxy->proxyy, proxy->proxyw,
			proxy->proxyh);
	}
}
