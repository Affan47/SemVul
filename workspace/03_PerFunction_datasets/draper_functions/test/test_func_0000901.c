bnxt_alloc_rx_page(struct bnxt *bp,
				     struct bnxt_rx_ring_info *rxr,
				     u16 prod, gfp_t gfp)
{
	struct rx_bd *rxbd =
		&rxr->rx_agg_desc_ring[RX_RING(prod)][RX_IDX(prod)];
	struct bnxt_sw_rx_agg_bd *rx_agg_buf;
	struct pci_dev *pdev = bp->pdev;
	struct page *page;
	dma_addr_t mapping;
	u16 sw_prod = rxr->rx_sw_agg_prod;

	page = alloc_page(gfp);
	if (!page)
		return -ENOMEM;

	mapping = dma_map_page(&pdev->dev, page, 0, PAGE_SIZE,
			       PCI_DMA_FROMDEVICE);
	if (dma_mapping_error(&pdev->dev, mapping)) {
		__free_page(page);
		return -EIO;
	}

	if (unlikely(test_bit(sw_prod, rxr->rx_agg_bmap)))
		sw_prod = bnxt_find_next_agg_idx(rxr, sw_prod);

	__set_bit(sw_prod, rxr->rx_agg_bmap);
	rx_agg_buf = &rxr->rx_agg_ring[sw_prod];
	rxr->rx_sw_agg_prod = NEXT_RX_AGG(sw_prod);

	rx_agg_buf->page = page;
	rx_agg_buf->mapping = mapping;
	rxbd->rx_bd_haddr = cpu_to_le64(mapping);
	rxbd->rx_bd_opaque = sw_prod;
	return 0;
}
