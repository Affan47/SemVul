wl3501_detach(struct pcmcia_device *link)
{
	struct net_device *dev = link->priv;


	while (link->open > 0)
		wl3501_close(dev);

	netif_device_detach(dev);
	wl3501_release(link);

	unregister_netdev(dev);

	if (link->priv)
		free_netdev(link->priv);
}
