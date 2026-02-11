bringup_one_dev(struct netdev *template, struct netdev *dev)
{
	if (template->ip_addr != INADDR_NONE)
		dev->ip_addr = template->ip_addr;
	if (template->ip_server != INADDR_NONE)
		dev->ip_server = template->ip_server;
	if (template->ip_gateway != INADDR_NONE)
		dev->ip_gateway = template->ip_gateway;
	if (template->ip_netmask != INADDR_NONE)
		dev->ip_netmask = template->ip_netmask;
	if (template->ip_nameserver[0] != INADDR_NONE)
		dev->ip_nameserver[0] = template->ip_nameserver[0];
	if (template->ip_nameserver[1] != INADDR_NONE)
		dev->ip_nameserver[1] = template->ip_nameserver[1];
	if (template->hostname[0] != '\0')
		strcpy(dev->hostname, template->hostname);
	if (template->reqhostname[0] != '\0')
		strcpy(dev->reqhostname, template->reqhostname);
	dev->caps &= template->caps;

	bringup_device(dev);
}
