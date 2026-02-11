rhine_refill_rx ( struct rhine_nic *rhn ) {
	struct rhine_descriptor *desc;
	struct io_buffer *iobuf;
	unsigned int rx_idx;
	physaddr_t address;

	while ( ( rhn->rx.prod - rhn->rx.cons ) < RHINE_RXDESC_NUM ) {


		iobuf = alloc_iob ( RHINE_RX_MAX_LEN );
		if ( ! iobuf ) {

			return;
		}


		rx_idx = ( rhn->rx.prod++ % RHINE_RXDESC_NUM );
		desc = &rhn->rx.desc[rx_idx];
		address = virt_to_bus ( iobuf->data );
		desc->buffer = cpu_to_le32 ( address );
		desc->des1 =
			cpu_to_le32 ( RHINE_DES1_SIZE ( RHINE_RX_MAX_LEN - 1) |
				      RHINE_DES1_CHAIN | RHINE_DES1_IC );
		wmb();
		desc->des0 = cpu_to_le32 ( RHINE_DES0_OWN );


		rhn->rx_iobuf[rx_idx] = iobuf;

		DBGC2 ( rhn, "RHINE %p RX %d is [%llx,%llx)\n", rhn, rx_idx,
			( ( unsigned long long ) address ),
			( ( unsigned long long ) address + RHINE_RX_MAX_LEN ) );
	}
}
