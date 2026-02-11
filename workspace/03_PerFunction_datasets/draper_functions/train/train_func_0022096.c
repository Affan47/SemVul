fcoe_add_netdev_mapping(struct net_device *netdev,
					struct fcoe_transport *ft)
{
	struct fcoe_netdev_mapping *nm;

	nm = kmalloc(sizeof(*nm), GFP_KERNEL);
	if (!nm) {
		printk(KERN_ERR "Unable to allocate netdev_mapping");
		return -ENOMEM;
	}

	nm->netdev = netdev;
	nm->ft = ft;

	mutex_lock(&fn_mutex);
	list_add(&nm->list, &fcoe_netdevs);
	mutex_unlock(&fn_mutex);
	return 0;
}
