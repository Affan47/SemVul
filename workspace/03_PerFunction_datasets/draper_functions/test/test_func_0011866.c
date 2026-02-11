bnx2_alloc_rx_page(struct bnx2 *bp, struct bnx2_rx_ring_info *rxr, u16 index, gfp_t gfp)
{
	dma_addr_t mapping;
	struct bnx2_sw_pg *rx_pg = &rxr->rx_pg_ring[index];
	struct bnx2_rx_bd *rxbd =
		&rxr->rx_pg_desc_ring[BNX2_RX_RING(index)][BNX2_RX_IDX(index)];
	struct page *page = alloc_page(gfp);

	if (!page)
		return -ENOMEM;
	mapping = dma_map_page(&bp->pdev->dev, page, 0, PAGE_SIZE,
			       PCI_DMA_FROMDEVICE);
	if (dma_mapping_error(&bp->pdev->dev, mapping)) {
		__free_page(page);
		return -EIO;
	}

	rx_pg->page = page;
	dma_unmap_addr_set(rx_pg, mapping, mapping);
	rxbd->rx_bd_haddr_hi = (u64) mapping >> 32;
	rxbd->rx_bd_haddr_lo = (u64) mapping & 0xffffffff;
	return 0;
}
