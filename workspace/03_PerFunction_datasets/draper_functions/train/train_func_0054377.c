sky2_device_event(struct notifier_block *unused,
			     unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct sky2_port *sky2 = netdev_priv(dev);

	if (dev->netdev_ops->ndo_open != sky2_open || !sky2_debug)
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_CHANGENAME:
		if (sky2->debugfs) {
			sky2->debugfs = debugfs_rename(sky2_debug, sky2->debugfs,
						       sky2_debug, dev->name);
		}
		break;

	case NETDEV_GOING_DOWN:
		if (sky2->debugfs) {
			netdev_printk(KERN_DEBUG, dev, "remove debugfs\n");
			debugfs_remove(sky2->debugfs);
			sky2->debugfs = NULL;
		}
		break;

	case NETDEV_UP:
		sky2->debugfs = debugfs_create_file(dev->name, S_IRUGO,
						    sky2_debug, dev,
						    &sky2_debug_fops);
		if (IS_ERR(sky2->debugfs))
			sky2->debugfs = NULL;
	}

	return NOTIFY_DONE;
}
