pcnet32_transmit ( struct net_device *netdev, struct io_buffer *iobuf )
{
	struct pcnet32_private *priv = netdev_priv ( netdev );
	unsigned long ioaddr = priv->pci_dev->ioaddr;
	uint32_t tx_len = iob_len ( iobuf );
	struct pcnet32_tx_desc *tx_curr_desc;

	DBGP ( "pcnet32_transmit\n" );

	if ( priv->tx_fill_ctr == TX_RING_SIZE ) {
		DBG ( "Tx overflow\n" );
		return -ENOTSUP;
	}

	priv->tx_iobuf[priv->tx_curr] = iobuf;

	tx_curr_desc = priv->tx_base + priv->tx_curr;


	tx_curr_desc->length = cpu_to_le16 ( -tx_len );
	tx_curr_desc->misc = 0x00000000;
	tx_curr_desc->base = cpu_to_le32 ( virt_to_bus ( iobuf->data ) );


	wmb();
	tx_curr_desc->status =
		cpu_to_le16 ( DescOwn | StartOfPacket | EndOfPacket );


	priv->a->write_csr ( ioaddr, 0,
		( priv->irq_enabled ? IntEnable : 0 ) | TxDemand );


	priv->tx_curr = ( priv->tx_curr + 1 ) % TX_RING_SIZE;


	priv->tx_fill_ctr++;

	return 0;
}
