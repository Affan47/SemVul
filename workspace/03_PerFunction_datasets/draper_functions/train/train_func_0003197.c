bnx2_alloc_rx_data(struct bnx2 *bp, struct bnx2_rx_ring_info *rxr, u16 index, gfp_t gfp)
{
	u8 *data;
	struct bnx2_sw_bd *rx_buf = &rxr->rx_buf_ring[index];
	dma_addr_t mapping;
	struct bnx2_rx_bd *rxbd =
		&rxr->rx_desc_ring[BNX2_RX_RING(index)][BNX2_RX_IDX(index)];

	data = kmalloc(bp->rx_buf_size, gfp);
	if (!data)
		return -ENOMEM;

	mapping = dma_map_single(&bp->pdev->dev,
				 get_l2_fhdr(data),
				 bp->rx_buf_use_size,
				 PCI_DMA_FROMDEVICE);
	if (dma_mapping_error(&bp->pdev->dev, mapping)) {
		kfree(data);
		return -EIO;
	}

	rx_buf->data = data;
	dma_unmap_addr_set(rx_buf, mapping, mapping);

	rxbd->rx_bd_haddr_hi = (u64) mapping >> 32;
	rxbd->rx_bd_haddr_lo = (u64) mapping & 0xffffffff;

	rxr->rx_prod_bseq += bp->rx_buf_use_size;

	return 0;
}
