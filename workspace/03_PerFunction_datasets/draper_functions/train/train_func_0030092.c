atl1e_setup_ring_resources(struct atl1e_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	struct atl1e_tx_ring *tx_ring;
	struct atl1e_rx_ring *rx_ring;
	struct atl1e_rx_page_desc  *rx_page_desc;
	int size, i, j;
	u32 offset = 0;
	int err = 0;

	if (adapter->ring_vir_addr != NULL)
		return 0;

	tx_ring = &adapter->tx_ring;
	rx_ring = &adapter->rx_ring;


	size = adapter->ring_size;
	adapter->ring_vir_addr = pci_zalloc_consistent(pdev, adapter->ring_size,
						       &adapter->ring_dma);
	if (adapter->ring_vir_addr == NULL) {
		netdev_err(adapter->netdev,
			   "pci_alloc_consistent failed, size = D%d\n", size);
		return -ENOMEM;
	}

	rx_page_desc = rx_ring->rx_page_desc;


	tx_ring->dma = roundup(adapter->ring_dma, 8);
	offset = tx_ring->dma - adapter->ring_dma;
	tx_ring->desc = adapter->ring_vir_addr + offset;
	size = sizeof(struct atl1e_tx_buffer) * (tx_ring->count);
	tx_ring->tx_buffer = kzalloc(size, GFP_KERNEL);
	if (tx_ring->tx_buffer == NULL) {
		err = -ENOMEM;
		goto failed;
	}


	offset += (sizeof(struct atl1e_tpd_desc) * tx_ring->count);
	offset = roundup(offset, 32);

	for (i = 0; i < adapter->num_rx_queues; i++) {
		for (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) {
			rx_page_desc[i].rx_page[j].dma =
				adapter->ring_dma + offset;
			rx_page_desc[i].rx_page[j].addr =
				adapter->ring_vir_addr + offset;
			offset += rx_ring->real_page_size;
		}
	}


	tx_ring->cmb_dma = adapter->ring_dma + offset;
	tx_ring->cmb = adapter->ring_vir_addr + offset;
	offset += sizeof(u32);

	for (i = 0; i < adapter->num_rx_queues; i++) {
		for (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) {
			rx_page_desc[i].rx_page[j].write_offset_dma =
				adapter->ring_dma + offset;
			rx_page_desc[i].rx_page[j].write_offset_addr =
				adapter->ring_vir_addr + offset;
			offset += sizeof(u32);
		}
	}

	if (unlikely(offset > adapter->ring_size)) {
		netdev_err(adapter->netdev, "offset(%d) > ring size(%d) !!\n",
			   offset, adapter->ring_size);
		err = -1;
		goto failed;
	}

	return 0;
failed:
	if (adapter->ring_vir_addr != NULL) {
		pci_free_consistent(pdev, adapter->ring_size,
				adapter->ring_vir_addr, adapter->ring_dma);
		adapter->ring_vir_addr = NULL;
	}
	return err;
}
