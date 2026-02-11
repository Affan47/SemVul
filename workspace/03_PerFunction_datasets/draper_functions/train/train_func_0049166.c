MarkProxy(ProxyWindow *new_proxy)
{
	ProxyWindow *old_proxy;

	old_proxy = selectProxy;
	selectProxy = new_proxy;
	if (selectProxy != old_proxy)
	{
		if (old_proxy != NULL)
		{
			DrawProxyBackground(old_proxy);
			DrawProxy(old_proxy);
		}
		if (selectProxy != NULL)
		{
			DrawProxyBackground(selectProxy);
			DrawProxy(selectProxy);
		}
	}
	if (old_proxy != NULL)
		send_command_to_fvwm(action_list[PROXY_ACTION_UNMARK],
				old_proxy->window);
	if (selectProxy != NULL)
		send_command_to_fvwm(action_list[PROXY_ACTION_MARK],
				selectProxy->window);

	if(showOnly && are_windows_shown)
	{
		ReshuffleWindows();
		selectProxy = new_proxy;
	}
	return;
}
