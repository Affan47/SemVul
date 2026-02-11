vrf_dev_init(struct net_device *dev)
{
	struct net_vrf *vrf = netdev_priv(dev);

	INIT_LIST_HEAD(&vrf->queue.all_slaves);

	dev->dstats = netdev_alloc_pcpu_stats(struct pcpu_dstats);
	if (!dev->dstats)
		goto out_nomem;


	vrf->rth = vrf_rtable_create(dev);
	if (!vrf->rth)
		goto out_stats;

	if (vrf_rt6_create(dev) != 0)
		goto out_rth;

	dev->flags = IFF_MASTER | IFF_NOARP;

	return 0;

out_rth:
	vrf_rtable_destroy(vrf);
out_stats:
	free_percpu(dev->dstats);
	dev->dstats = NULL;
out_nomem:
	return -ENOMEM;
}
