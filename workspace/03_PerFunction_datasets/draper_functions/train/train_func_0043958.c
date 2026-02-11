visornic_resume(struct visor_device *dev,
			   visorbus_state_complete_func complete_func)
{
	struct visornic_devdata *devdata;
	struct net_device *netdev;
	unsigned long flags;

	devdata = dev_get_drvdata(&dev->device);
	if (!devdata) {
		dev_err(&dev->device, "%s no devdata\n", __func__);
		return -EINVAL;
	}

	netdev = devdata->netdev;

	spin_lock_irqsave(&devdata->priv_lock, flags);
	if (devdata->server_change_state) {
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		dev_err(&dev->device, "%s server already changing state\n",
			__func__);
		return -EINVAL;
	}
	if (!devdata->server_down) {
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		dev_err(&dev->device, "%s server not down\n", __func__);
		complete_func(dev, 0);
		return 0;
	}
	devdata->server_change_state = true;
	spin_unlock_irqrestore(&devdata->priv_lock, flags);


	mod_timer(&devdata->irq_poll_timer, msecs_to_jiffies(2));

	init_rcv_bufs(netdev, devdata);

	rtnl_lock();
	dev_open(netdev);
	rtnl_unlock();

	complete_func(dev, 0);
	return 0;
}
