dlci_add(struct dlci_add *dlci)
{
	struct net_device	*master, *slave;
	struct dlci_local	*dlp;
	struct frad_local	*flp;
	int			err = -EINVAL;


	slave = dev_get_by_name(&init_net, dlci->devname);
	if (!slave)
		return -ENODEV;

	if (slave->type != ARPHRD_FRAD || netdev_priv(slave) == NULL)
		goto err1;


	master = alloc_netdev(sizeof(struct dlci_local), "dlci%d",
			      NET_NAME_UNKNOWN, dlci_setup);
	if (!master) {
		err = -ENOMEM;
		goto err1;
	}


	rtnl_lock();
	list_for_each_entry(dlp, &dlci_devs, list) {
		if (dlp->slave == slave) {
			err = -EBUSY;
			goto err2;
		}
	}

	*(short *)(master->dev_addr) = dlci->dlci;

	dlp = netdev_priv(master);
	dlp->slave = slave;
	dlp->master = master;

	flp = netdev_priv(slave);
	err = (*flp->assoc)(slave, master);
	if (err < 0)
		goto err2;

	err = register_netdevice(master);
	if (err < 0)
		goto err2;

	strcpy(dlci->devname, master->name);

	list_add(&dlp->list, &dlci_devs);
	rtnl_unlock();

	return 0;

 err2:
	rtnl_unlock();
	free_netdev(master);
 err1:
	dev_put(slave);
	return err;
}
