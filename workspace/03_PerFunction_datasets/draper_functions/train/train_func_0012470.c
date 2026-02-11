netxen_config_indev_addr(struct netxen_adapter *adapter,
		struct net_device *dev, unsigned long event)
{
	struct in_device *indev;

	if (!netxen_destip_supported(adapter))
		return;

	indev = in_dev_get(dev);
	if (!indev)
		return;

	for_ifa(indev) {
		switch (event) {
		case NETDEV_UP:
			netxen_list_config_ip(adapter, ifa, NX_IP_UP);
			break;
		case NETDEV_DOWN:
			netxen_list_config_ip(adapter, ifa, NX_IP_DOWN);
			break;
		default:
			break;
		}
	} endfor_ifa(indev);

	in_dev_put(indev);
}
