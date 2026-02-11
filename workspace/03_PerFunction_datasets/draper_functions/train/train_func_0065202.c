pch_gbe_alloc_rx_buffers_pool(struct pch_gbe_adapter *adapter,
			 struct pch_gbe_rx_ring *rx_ring, int cleaned_count)
{
	struct pci_dev *pdev = adapter->pdev;
	struct pch_gbe_buffer *buffer_info;
	unsigned int i;
	unsigned int bufsz;
	unsigned int size;

	bufsz = adapter->rx_buffer_len;

	size = rx_ring->count * bufsz + PCH_GBE_RESERVE_MEMORY;
	rx_ring->rx_buff_pool =
		dma_zalloc_coherent(&pdev->dev, size,
				    &rx_ring->rx_buff_pool_logic, GFP_KERNEL);
	if (!rx_ring->rx_buff_pool)
		return -ENOMEM;

	rx_ring->rx_buff_pool_size = size;
	for (i = 0; i < rx_ring->count; i++) {
		buffer_info = &rx_ring->buffer_info[i];
		buffer_info->rx_buffer = rx_ring->rx_buff_pool + bufsz * i;
		buffer_info->length = bufsz;
	}
	return 0;
}
