pch_gbe_clean_rx_ring(struct pch_gbe_adapter *adapter,
		      struct pch_gbe_rx_ring *rx_ring)
{
	struct pch_gbe_hw *hw = &adapter->hw;
	struct pch_gbe_buffer *buffer_info;
	unsigned long size;
	unsigned int i;


	for (i = 0; i < rx_ring->count; i++) {
		buffer_info = &rx_ring->buffer_info[i];
		pch_gbe_unmap_and_free_rx_resource(adapter, buffer_info);
	}
	netdev_dbg(adapter->netdev,
		   "call pch_gbe_unmap_and_free_rx_resource() %d count\n", i);
	size = (unsigned long)sizeof(struct pch_gbe_buffer) * rx_ring->count;
	memset(rx_ring->buffer_info, 0, size);


	memset(rx_ring->desc, 0, rx_ring->size);
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
	iowrite32(rx_ring->dma, &hw->reg->RX_DSC_HW_P);
	iowrite32((rx_ring->size - 0x10), &hw->reg->RX_DSC_SIZE);
}
