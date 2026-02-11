ifec_net_close ( struct net_device *netdev )
{
	struct ifec_private *priv = netdev->priv;
	unsigned long ioaddr = priv->ioaddr;
	unsigned short intr_status;

	DBGP ( "ifec_net_close\n" );


	ifec_net_irq ( netdev, 0 );


	intr_status = inw ( ioaddr + SCBStatus );
	outw ( intr_status, ioaddr + SCBStatus );
	inw ( ioaddr + SCBStatus );

	ifec_reset ( netdev );


	ifec_free ( netdev );
}
