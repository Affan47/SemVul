forcedeth_remove ( struct pci_device *pdev )
{
	struct net_device *netdev = pci_get_drvdata ( pdev );
	struct forcedeth_private *priv = netdev->priv;

	DBGP ( "forcedeth_remove\n" );

	unregister_netdev ( netdev );

	nv_restore_phy ( priv );

	nv_mgmt_release_sema ( priv );

	iounmap ( priv->mmio_addr );

	netdev_nullify ( netdev );
	netdev_put ( netdev );
}
