rhine_remove ( struct pci_device *pci ) {
	struct net_device *netdev = pci_get_drvdata ( pci );
	struct rhine_nic *nic = netdev->priv;


	unregister_netdev ( netdev );


	rhine_reset ( nic );


	netdev_nullify ( netdev );
	netdev_put ( netdev );
}
