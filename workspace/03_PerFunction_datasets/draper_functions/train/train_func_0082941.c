rtl_transmit ( struct net_device *netdev,
			  struct io_buffer *iobuf ) {
	struct rtl8139_nic *rtl = netdev->priv;


	if ( rtl->tx.iobuf[rtl->tx.next] != NULL ) {
		DBGC ( rtl, "rtl8139 %p TX overflow\n", rtl );
		return -ENOBUFS;
	}


	iob_pad ( iobuf, ETH_ZLEN );


	DBGC2 ( rtl, "rtl8139 %p TX id %d at %lx+%zx\n", rtl, rtl->tx.next,
		virt_to_bus ( iobuf->data ), iob_len ( iobuf ) );
	rtl->tx.iobuf[rtl->tx.next] = iobuf;
	outl ( virt_to_bus ( iobuf->data ),
	       rtl->ioaddr + TxAddr0 + 4 * rtl->tx.next );
	outl ( ( ( ( TX_FIFO_THRESH & 0x7e0 ) << 11 ) | iob_len ( iobuf ) ),
	       rtl->ioaddr + TxStatus0 + 4 * rtl->tx.next );
	rtl->tx.next = ( rtl->tx.next + 1 ) % TX_RING_SIZE;

	return 0;
}
