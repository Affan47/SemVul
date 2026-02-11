atmel_release(struct pcmcia_device *link)
{
	struct net_device *dev = ((struct local_info *)link->priv)->eth_dev;

	dev_dbg(&link->dev, "atmel_release\n");

	if (dev)
		stop_atmel_card(dev);
	((struct local_info *)link->priv)->eth_dev = NULL;

	pcmcia_disable_device(link);
}
