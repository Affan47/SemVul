qlcnic_config_indev_addr(struct qlcnic_adapter *adapter,
			struct net_device *dev, unsigned long event)
{
	struct in_device *indev;

	indev = in_dev_get(dev);
	if (!indev)
		return;

	for_ifa(indev) {
		switch (event) {
		case NETDEV_UP:
			qlcnic_config_ipaddr(adapter,
					ifa->ifa_address, QLCNIC_IP_UP);
			break;
		case NETDEV_DOWN:
			qlcnic_config_ipaddr(adapter,
					ifa->ifa_address, QLCNIC_IP_DOWN);
			break;
		default:
			break;
		}
	} endfor_ifa(indev);

	in_dev_put(indev);
}
