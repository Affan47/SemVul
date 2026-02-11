par96_wakeup(void *handle)
{
        struct net_device *dev = (struct net_device *)handle;
	struct baycom_state *bc = netdev_priv(dev);

	printk(KERN_DEBUG "baycom_par: %s: why am I being woken up?\n", dev->name);
	if (!parport_claim(bc->pdev))
		printk(KERN_DEBUG "baycom_par: %s: I'm broken.\n", dev->name);
}
