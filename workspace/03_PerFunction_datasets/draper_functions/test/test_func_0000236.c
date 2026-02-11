most_net_rm_netdev_safe(struct net_dev_context *nd)
{
	if (!nd->dev)
		return;

	pr_info("remove net device %p\n", nd->dev);

	unregister_netdev(nd->dev);
	free_netdev(nd->dev);
	nd->dev = NULL;
}
