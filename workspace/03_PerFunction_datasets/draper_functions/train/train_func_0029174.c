hdlcdev_tx_timeout(struct net_device *dev)
{
	SLMP_INFO *info = dev_to_port(dev);
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("hdlcdev_tx_timeout(%s)\n",dev->name);

	dev->stats.tx_errors++;
	dev->stats.tx_aborted_errors++;

	spin_lock_irqsave(&info->lock,flags);
	tx_stop(info);
	spin_unlock_irqrestore(&info->lock,flags);

	netif_wake_queue(dev);
}
