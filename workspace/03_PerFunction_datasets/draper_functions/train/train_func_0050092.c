uli526x_dynamic_reset(struct net_device *dev)
{
	ULI526X_DBUG(0, "uli526x_dynamic_reset()", 0);

	uli526x_reset_prepare(dev);


	uli526x_init(dev);


	netif_wake_queue(dev);
}
