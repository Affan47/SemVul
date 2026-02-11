fm10k_max_channels(struct net_device *dev)
{
	struct fm10k_intfc *interface = netdev_priv(dev);
	unsigned int max_combined = interface->hw.mac.max_queues;
	u8 tcs = netdev_get_num_tc(dev);


	if (tcs > 1)
		max_combined = 1 << (fls(max_combined / tcs) - 1);

	return max_combined;
}
