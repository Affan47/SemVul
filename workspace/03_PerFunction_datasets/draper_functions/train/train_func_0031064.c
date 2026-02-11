intel_refill_rx ( struct intel_nic *intel ) {
	struct intel_descriptor *rx;
	struct io_buffer *iobuf;
	unsigned int rx_idx;
	unsigned int rx_tail;
	physaddr_t address;

	while ( ( intel->rx.prod - intel->rx.cons ) < INTEL_RX_FILL ) {


		iobuf = alloc_iob ( INTEL_RX_MAX_LEN );
		if ( ! iobuf ) {

			return;
		}


		rx_idx = ( intel->rx.prod++ % INTEL_NUM_RX_DESC );
		rx_tail = ( intel->rx.prod % INTEL_NUM_RX_DESC );
		rx = &intel->rx.desc[rx_idx];


		address = virt_to_bus ( iobuf->data );
		rx->address = cpu_to_le64 ( address );
		rx->length = 0;
		rx->status = 0;
		rx->errors = 0;
		wmb();


		assert ( intel->rx_iobuf[rx_idx] == NULL );
		intel->rx_iobuf[rx_idx] = iobuf;


		writel ( rx_tail, intel->regs + intel->rx.reg + INTEL_xDT );

		DBGC2 ( intel, "INTEL %p RX %d is [%llx,%llx)\n", intel, rx_idx,
			( ( unsigned long long ) address ),
			( ( unsigned long long ) address + INTEL_RX_MAX_LEN ) );
	}
}
