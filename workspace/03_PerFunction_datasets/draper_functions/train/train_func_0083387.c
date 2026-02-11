atl1e_init_ring_ptrs(struct atl1e_adapter *adapter)
{
	struct atl1e_tx_ring *tx_ring = NULL;
	struct atl1e_rx_ring *rx_ring = NULL;
	struct atl1e_rx_page_desc *rx_page_desc = NULL;
	int i, j;

	tx_ring = &adapter->tx_ring;
	rx_ring = &adapter->rx_ring;
	rx_page_desc = rx_ring->rx_page_desc;

	tx_ring->next_to_use = 0;
	atomic_set(&tx_ring->next_to_clean, 0);

	for (i = 0; i < adapter->num_rx_queues; i++) {
		rx_page_desc[i].rx_using  = 0;
		rx_page_desc[i].rx_nxseq = 0;
		for (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) {
			*rx_page_desc[i].rx_page[j].write_offset_addr = 0;
			rx_page_desc[i].rx_page[j].read_offset = 0;
		}
	}
}
