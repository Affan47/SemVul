lapbeth_device_event(struct notifier_block *this,
				unsigned long event, void *ptr)
{
	struct lapbethdev *lapbeth;
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);

	if (dev_net(dev) != &init_net)
		return NOTIFY_DONE;

	if (!dev_is_ethdev(dev))
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:

		if (lapbeth_get_x25_dev(dev) == NULL)
			lapbeth_new_device(dev);
		break;
	case NETDEV_DOWN:

		lapbeth = lapbeth_get_x25_dev(dev);
		if (lapbeth)
			dev_close(lapbeth->axdev);
		break;
	case NETDEV_UNREGISTER:

		lapbeth = lapbeth_get_x25_dev(dev);
		if (lapbeth)
			lapbeth_free_device(lapbeth);
		break;
	}

	return NOTIFY_DONE;
}
