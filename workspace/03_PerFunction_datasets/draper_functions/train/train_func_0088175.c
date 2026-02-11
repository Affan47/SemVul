FindProxyGroupOfNeighbor(ProxyWindow* instigator)
{
	ProxyWindow *proxy;

	if(!instigator->group)
	{
		return NULL;
	}

	for (proxy=firstProxy; proxy != NULL; proxy=proxy->next)
	{
		if(proxy==instigator)
		{
			continue;
		}
		if (proxy->desk == deskNumber &&
			proxy->group==instigator->group && proxy->proxy_group)
		{
			return proxy->proxy_group;
		}
	}
	return NULL;
}
