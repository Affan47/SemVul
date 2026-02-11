vmxnet3_refill_rx ( struct net_device *netdev ) {
	struct vmxnet3_nic *vmxnet = netdev_priv ( netdev );
	struct vmxnet3_rx_desc *rx_desc;
	struct io_buffer *iobuf;
	unsigned int orig_rx_prod = vmxnet->count.rx_prod;
	unsigned int desc_idx;
	unsigned int generation;


	while ( vmxnet->count.rx_fill < VMXNET3_RX_FILL ) {


		desc_idx = ( vmxnet->count.rx_prod % VMXNET3_NUM_RX_DESC );
		generation = ( ( vmxnet->count.rx_prod & VMXNET3_NUM_RX_DESC ) ?
			       0 : cpu_to_le32 ( VMXNET3_RXF_GEN ) );
		assert ( vmxnet->rx_iobuf[desc_idx] == NULL );


		iobuf = alloc_iob ( VMXNET3_MTU + NET_IP_ALIGN );
		if ( ! iobuf ) {

			break;
		}
		iob_reserve ( iobuf, NET_IP_ALIGN );


		vmxnet->count.rx_prod++;
		vmxnet->count.rx_fill++;


		vmxnet->rx_iobuf[desc_idx] = iobuf;


		rx_desc = &vmxnet->dma->rx_desc[desc_idx];
		rx_desc->address = cpu_to_le64 ( virt_to_bus ( iobuf->data ) );
		rx_desc->flags = ( generation | cpu_to_le32 ( VMXNET3_MTU ) );

	}


	if ( vmxnet->count.rx_prod != orig_rx_prod ) {
		wmb();
		writel ( ( vmxnet->count.rx_prod % VMXNET3_NUM_RX_DESC ),
			 ( vmxnet->pt + VMXNET3_PT_RXPROD ) );
	}
}
