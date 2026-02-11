ReadStack(unsigned long *body, unsigned long length)
{
	Window window;
	ProxyWindow *proxy;
	int i;
	ProxyWindow *instigator=NULL;
	int index;

#if PROXY_GROUP_DEBUG
	fprintf(stderr, "ReadStack %p %d-%d\n",
		body, (int)length, FvwmPacketHeaderSize);
#endif

	for (i = 0; i < (length - FvwmPacketHeaderSize); i += 3)
	{
		instigator=FindProxy(body[0]);
		if(instigator)
		{
			break;
		}
	}
	if(!instigator)
	{
		return;
	}
	for (proxy=firstProxy; proxy != NULL; proxy=proxy->next)
	{
		if(proxy->stack>instigator->stack)
		{
			proxy->stack+=10000;
		}
	}

	index=instigator->stack;
	for (i = 0; i < (length - FvwmPacketHeaderSize); i += 3)
	{
		window = body[i];
#if PROXY_GROUP_DEBUG
		fprintf(stderr, "  stack %d %d\n", i, (int)window);
#endif
		proxy = FindProxy(window);
		if(proxy)
		{
#if PROXY_GROUP_DEBUG
			fprintf(stderr, " %p %s",proxy,proxy->name);
#endif
			proxy->stack = index++;
		}
#if PROXY_GROUP_DEBUG
		fprintf(stderr, "\n");
#endif
	}
	RefineStack(False);
}
