tlan_tx_timeout(struct net_device *dev)
{

	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Transmit timed out.\n", dev->name);


	tlan_free_lists(dev);
	tlan_reset_lists(dev);
	tlan_read_and_clear_stats(dev, TLAN_IGNORE);
	tlan_reset_adapter(dev);
	dev->trans_start = jiffies;
	netif_wake_queue(dev);

}
