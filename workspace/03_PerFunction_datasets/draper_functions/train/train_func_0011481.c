nv_start_rx ( struct forcedeth_private *priv )
{
	void *ioaddr = priv->mmio_addr;
	u32 rx_ctrl = readl ( ioaddr + NvRegReceiverControl );

	DBGP ( "nv_start_rx\n" );

	if ( ( readl ( ioaddr + NvRegReceiverControl ) & NVREG_RCVCTL_START ) && !priv->mac_in_use ) {
		rx_ctrl &= ~NVREG_RCVCTL_START;
		writel ( rx_ctrl, ioaddr + NvRegReceiverControl );
		pci_push ( ioaddr );
	}
	writel ( priv->linkspeed, ioaddr + NvRegLinkSpeed );
	pci_push ( ioaddr );
        rx_ctrl |= NVREG_RCVCTL_START;
        if ( priv->mac_in_use )
		rx_ctrl &= ~NVREG_RCVCTL_RX_PATH_EN;
	writel ( rx_ctrl, ioaddr + NvRegReceiverControl );
	DBG ( "nv_start_rx to duplex %d, speed 0x%08x.\n",
		priv->duplex, priv->linkspeed);
	pci_push ( ioaddr );
}
