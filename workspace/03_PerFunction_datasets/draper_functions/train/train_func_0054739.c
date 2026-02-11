pcnet_release(struct pcmcia_device *link)
{
	struct pcnet_dev *info = PRIV(link->priv);

	dev_dbg(&link->dev, "pcnet_release\n");

	if (info->flags & USE_SHMEM)
		iounmap(info->base);

	pcmcia_disable_device(link);
}
