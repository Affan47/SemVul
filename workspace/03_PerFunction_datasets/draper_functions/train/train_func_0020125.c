natsemi_refill_rx ( struct net_device *netdev ) {
	struct natsemi_nic *natsemi = netdev->priv;
	union natsemi_descriptor *rx;
	struct io_buffer *iobuf;
	unsigned int rx_idx;
	physaddr_t address;

	while ( ( natsemi->rx.prod - natsemi->rx.cons ) < NATSEMI_NUM_RX_DESC ){


		iobuf = alloc_iob ( NATSEMI_RX_MAX_LEN );
		if ( ! iobuf ) {

			return;
		}


		address = virt_to_bus ( iobuf->data );
		if ( ! natsemi_address_ok ( natsemi, address ) ) {
			DBGC ( natsemi, "NATSEMI %p cannot support 64-bit RX "
			       "buffer address\n", natsemi );
			netdev_rx_err ( netdev, iobuf, -ENOTSUP );
			return;
		}


		rx_idx = ( natsemi->rx.prod++ % NATSEMI_NUM_RX_DESC );
		rx = &natsemi->rx.desc[rx_idx];


		if ( natsemi->flags & NATSEMI_64BIT ) {
			rx->d64.bufptr = cpu_to_le64 ( address );
		} else {
			rx->d32pad.d32.bufptr = cpu_to_le32 ( address );
		}
		wmb();
		rx->common.cmdsts = cpu_to_le32 ( NATSEMI_DESC_INTR |
						  NATSEMI_RX_MAX_LEN );
		wmb();


		assert ( natsemi->rx_iobuf[rx_idx] == NULL );
		natsemi->rx_iobuf[rx_idx] = iobuf;


		writel ( NATSEMI_CR_RXE, natsemi->regs + NATSEMI_CR );

		DBGC2 ( natsemi, "NATSEMI %p RX %d is [%llx,%llx)\n", natsemi,
			rx_idx, ( ( unsigned long long ) address ),
			( ( unsigned long long ) address + NATSEMI_RX_MAX_LEN));
	}
}
