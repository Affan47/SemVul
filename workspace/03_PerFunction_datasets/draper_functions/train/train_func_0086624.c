liquidio_destroy_nic_device(struct octeon_device *oct, int ifidx)
{
	struct net_device *netdev = oct->props[ifidx].netdev;
	struct lio *lio;

	if (!netdev) {
		dev_err(&oct->pci_dev->dev, "%s No netdevice ptr for index %d\n",
			__func__, ifidx);
		return;
	}

	lio = GET_LIO(netdev);

	dev_dbg(&oct->pci_dev->dev, "NIC device cleanup\n");

	send_rx_ctrl_cmd(lio, 0);

	if (atomic_read(&lio->ifstate) & LIO_IFSTATE_RUNNING)
		txqs_stop(netdev);

	if (atomic_read(&lio->ifstate) & LIO_IFSTATE_REGISTERED)
		unregister_netdev(netdev);

	delete_glist(lio);

	free_netdev(netdev);

	oct->props[ifidx].netdev = NULL;
}
