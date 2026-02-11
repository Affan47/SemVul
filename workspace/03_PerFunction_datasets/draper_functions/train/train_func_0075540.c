vmxnet3_transmit ( struct net_device *netdev,
			      struct io_buffer *iobuf ) {
	struct vmxnet3_nic *vmxnet = netdev_priv ( netdev );
	struct vmxnet3_tx_desc *tx_desc;
	unsigned int desc_idx;
	unsigned int generation;


	desc_idx = ( vmxnet->count.tx_prod % VMXNET3_NUM_TX_DESC );
	generation = ( ( vmxnet->count.tx_prod & VMXNET3_NUM_TX_DESC ) ?
		       0 : cpu_to_le32 ( VMXNET3_TXF_GEN ) );
	if ( vmxnet->tx_iobuf[desc_idx] ) {
		DBGC ( vmxnet, "VMXNET3 %p out of transmit descriptors\n",
		       vmxnet );
		return -ENOBUFS;
	}


	vmxnet->count.tx_prod++;


	vmxnet->tx_iobuf[desc_idx] = iobuf;


	tx_desc = &vmxnet->dma->tx_desc[desc_idx];
	tx_desc->address = cpu_to_le64 ( virt_to_bus ( iobuf->data ) );
	tx_desc->flags[0] = ( generation | cpu_to_le32 ( iob_len ( iobuf ) ) );
	tx_desc->flags[1] = cpu_to_le32 ( VMXNET3_TXF_CQ | VMXNET3_TXF_EOP );


	wmb();
	writel ( ( vmxnet->count.tx_prod % VMXNET3_NUM_TX_DESC ),
		 ( vmxnet->pt + VMXNET3_PT_TXPROD ) );

	return 0;
}
