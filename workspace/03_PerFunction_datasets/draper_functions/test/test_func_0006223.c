myson_transmit ( struct net_device *netdev,
			    struct io_buffer *iobuf ) {
	struct myson_nic *myson = netdev->priv;
	struct myson_descriptor *tx;
	unsigned int tx_idx;
	physaddr_t address;


	address = virt_to_bus ( iobuf->data );
	if ( ! myson_address_ok ( address ) ) {
		DBGC ( myson, "MYSON %p cannot support 64-bit TX buffer "
		       "address\n", myson );
		return -ENOTSUP;
	}


	if ( ( myson->tx.prod - myson->tx.cons ) >= MYSON_NUM_TX_DESC ) {
		DBGC ( myson, "MYSON %p out of transmit descriptors\n",
		       myson );
		return -ENOBUFS;
	}
	tx_idx = ( myson->tx.prod++ % MYSON_NUM_TX_DESC );
	tx = &myson->tx.desc[tx_idx];


	tx->address = cpu_to_le32 ( address );
	tx->control = cpu_to_le32 ( MYSON_TX_CTRL_IC | MYSON_TX_CTRL_LD |
				    MYSON_TX_CTRL_FD | MYSON_TX_CTRL_CRC |
				    MYSON_TX_CTRL_PAD | MYSON_TX_CTRL_RTLC |
				    MYSON_TX_CTRL_PKTS ( iob_len ( iobuf ) ) |
				    MYSON_TX_CTRL_TBS ( iob_len ( iobuf ) ) );
	wmb();
	tx->status = cpu_to_le32 ( MYSON_TX_STAT_OWN );
	wmb();


	writel ( 0, myson->regs + MYSON_TXPDR );

	DBGC2 ( myson, "MYSON %p TX %d is [%llx,%llx)\n", myson, tx_idx,
		( ( unsigned long long ) address ),
		( ( unsigned long long ) address + iob_len ( iobuf ) ) );

	return 0;
}
