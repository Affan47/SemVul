bnx2_reuse_rx_data(struct bnx2 *bp, struct bnx2_rx_ring_info *rxr,
		   u8 *data, u16 cons, u16 prod)
{
	struct bnx2_sw_bd *cons_rx_buf, *prod_rx_buf;
	struct bnx2_rx_bd *cons_bd, *prod_bd;

	cons_rx_buf = &rxr->rx_buf_ring[cons];
	prod_rx_buf = &rxr->rx_buf_ring[prod];

	dma_sync_single_for_device(&bp->pdev->dev,
		dma_unmap_addr(cons_rx_buf, mapping),
		BNX2_RX_OFFSET + BNX2_RX_COPY_THRESH, PCI_DMA_FROMDEVICE);

	rxr->rx_prod_bseq += bp->rx_buf_use_size;

	prod_rx_buf->data = data;

	if (cons == prod)
		return;

	dma_unmap_addr_set(prod_rx_buf, mapping,
			dma_unmap_addr(cons_rx_buf, mapping));

	cons_bd = &rxr->rx_desc_ring[BNX2_RX_RING(cons)][BNX2_RX_IDX(cons)];
	prod_bd = &rxr->rx_desc_ring[BNX2_RX_RING(prod)][BNX2_RX_IDX(prod)];
	prod_bd->rx_bd_haddr_hi = cons_bd->rx_bd_haddr_hi;
	prod_bd->rx_bd_haddr_lo = cons_bd->rx_bd_haddr_lo;
}
