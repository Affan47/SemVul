pcnet32_close ( struct net_device *netdev )
{
	struct pcnet32_private *priv = netdev_priv ( netdev );
	unsigned long ioaddr = priv->pci_dev->ioaddr;

	DBGP ( "pcnet32_close\n" );


	pcnet32_wio_reset ( ioaddr );


	priv->a->write_csr ( ioaddr, 0, Stop );


	priv->a->write_bcr ( ioaddr, 20, PCNET32_SWSTYLE_LANCE );

	pcnet32_free_rx_resources ( priv );
	pcnet32_free_tx_resources ( priv );
}
