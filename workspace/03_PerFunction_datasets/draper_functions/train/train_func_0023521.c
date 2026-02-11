rtl8169_close ( struct net_device *netdev )
{
	struct rtl8169_private *tp = netdev_priv ( netdev );
	void *ioaddr = tp->mmio_addr;

	DBGP ( "r8169_close\n" );

	rtl8169_hw_reset ( ioaddr );

	rtl8169_free_tx_resources ( tp );
	rtl8169_free_rx_resources ( tp );
}
