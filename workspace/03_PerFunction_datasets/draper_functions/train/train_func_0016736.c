e1000_remove ( struct pci_device *pdev )
{
	struct net_device *netdev = pci_get_drvdata ( pdev );
	struct e1000_adapter *adapter = netdev_priv ( netdev );

	DBG ( "e1000_remove\n" );

	if ( adapter->hw.flash_address )
		iounmap ( adapter->hw.flash_address );
	if  ( adapter->hw.hw_addr )
		iounmap ( adapter->hw.hw_addr );

	unregister_netdev ( netdev );
	e1000_reset_hw ( &adapter->hw );
	netdev_nullify ( netdev );
	netdev_put ( netdev );
}
