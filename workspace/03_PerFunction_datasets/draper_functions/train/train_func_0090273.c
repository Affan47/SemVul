nlmon_dev_init(struct net_device *dev)
{
	dev->lstats = netdev_alloc_pcpu_stats(struct pcpu_lstats);
	return dev->lstats == NULL ? -ENOMEM : 0;
}
