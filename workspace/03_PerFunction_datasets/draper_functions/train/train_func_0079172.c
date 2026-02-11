bnxt_init_ring_struct(struct bnxt *bp)
{
	int i;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr;
		struct bnxt_rx_ring_info *rxr;
		struct bnxt_tx_ring_info *txr;
		struct bnxt_ring_struct *ring;

		if (!bnapi)
			continue;

		cpr = &bnapi->cp_ring;
		ring = &cpr->cp_ring_struct;
		ring->nr_pages = bp->cp_nr_pages;
		ring->page_size = HW_CMPD_RING_SIZE;
		ring->pg_arr = (void **)cpr->cp_desc_ring;
		ring->dma_arr = cpr->cp_desc_mapping;
		ring->vmem_size = 0;

		rxr = &bnapi->rx_ring;
		ring = &rxr->rx_ring_struct;
		ring->nr_pages = bp->rx_nr_pages;
		ring->page_size = HW_RXBD_RING_SIZE;
		ring->pg_arr = (void **)rxr->rx_desc_ring;
		ring->dma_arr = rxr->rx_desc_mapping;
		ring->vmem_size = SW_RXBD_RING_SIZE * bp->rx_nr_pages;
		ring->vmem = (void **)&rxr->rx_buf_ring;

		ring = &rxr->rx_agg_ring_struct;
		ring->nr_pages = bp->rx_agg_nr_pages;
		ring->page_size = HW_RXBD_RING_SIZE;
		ring->pg_arr = (void **)rxr->rx_agg_desc_ring;
		ring->dma_arr = rxr->rx_agg_desc_mapping;
		ring->vmem_size = SW_RXBD_AGG_RING_SIZE * bp->rx_agg_nr_pages;
		ring->vmem = (void **)&rxr->rx_agg_ring;

		txr = &bnapi->tx_ring;
		ring = &txr->tx_ring_struct;
		ring->nr_pages = bp->tx_nr_pages;
		ring->page_size = HW_RXBD_RING_SIZE;
		ring->pg_arr = (void **)txr->tx_desc_ring;
		ring->dma_arr = txr->tx_desc_mapping;
		ring->vmem_size = SW_TXBD_RING_SIZE * bp->tx_nr_pages;
		ring->vmem = (void **)&txr->tx_buf_ring;
	}
}
