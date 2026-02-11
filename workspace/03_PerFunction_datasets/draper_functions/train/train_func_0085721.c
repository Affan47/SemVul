cnic_init_bnx2_rx_ring(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_eth_dev *ethdev = cp->ethdev;
	struct cnic_uio_dev *udev = cp->udev;
	u32 cid_addr, sb_id, val, coal_reg, coal_val;
	int i;
	struct bnx2_rx_bd *rxbd;
	struct status_block *s_blk = cp->status_blk.gen;
	dma_addr_t ring_map = udev->l2_ring_map;

	sb_id = cp->status_blk_num;
	cnic_init_context(dev, 2);
	cp->rx_cons_ptr = &s_blk->status_rx_quick_consumer_index2;
	coal_reg = BNX2_HC_COMMAND;
	coal_val = CNIC_RD(dev, coal_reg);
	if (ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX) {
		struct status_block_msix *sblk = cp->status_blk.bnx2;

		cp->rx_cons_ptr = &sblk->status_rx_quick_consumer_index;
		coal_reg = BNX2_HC_COALESCE_NOW;
		coal_val = 1 << (11 + sb_id);
	}
	i = 0;
	while (!(*cp->rx_cons_ptr != 0) && i < 10) {
		CNIC_WR(dev, coal_reg, coal_val);
		udelay(10);
		i++;
		barrier();
	}
	cp->rx_cons = *cp->rx_cons_ptr;

	cid_addr = GET_CID_ADDR(2);
	val = BNX2_L2CTX_CTX_TYPE_CTX_BD_CHN_TYPE_VALUE |
	      BNX2_L2CTX_CTX_TYPE_SIZE_L2 | (0x02 << 8);
	cnic_ctx_wr(dev, cid_addr, BNX2_L2CTX_CTX_TYPE, val);

	if (sb_id == 0)
		val = 2 << BNX2_L2CTX_L2_STATUSB_NUM_SHIFT;
	else
		val = BNX2_L2CTX_L2_STATUSB_NUM(sb_id);
	cnic_ctx_wr(dev, cid_addr, BNX2_L2CTX_HOST_BDIDX, val);

	rxbd = udev->l2_ring + CNIC_PAGE_SIZE;
	for (i = 0; i < BNX2_MAX_RX_DESC_CNT; i++, rxbd++) {
		dma_addr_t buf_map;
		int n = (i % cp->l2_rx_ring_size) + 1;

		buf_map = udev->l2_buf_map + (n * cp->l2_single_buf_size);
		rxbd->rx_bd_len = cp->l2_single_buf_size;
		rxbd->rx_bd_flags = RX_BD_FLAGS_START | RX_BD_FLAGS_END;
		rxbd->rx_bd_haddr_hi = (u64) buf_map >> 32;
		rxbd->rx_bd_haddr_lo = (u64) buf_map & 0xffffffff;
	}
	val = (u64) (ring_map + CNIC_PAGE_SIZE) >> 32;
	cnic_ctx_wr(dev, cid_addr, BNX2_L2CTX_NX_BDHADDR_HI, val);
	rxbd->rx_bd_haddr_hi = val;

	val = (u64) (ring_map + CNIC_PAGE_SIZE) & 0xffffffff;
	cnic_ctx_wr(dev, cid_addr, BNX2_L2CTX_NX_BDHADDR_LO, val);
	rxbd->rx_bd_haddr_lo = val;

	val = cnic_reg_rd_ind(dev, BNX2_RXP_SCRATCH_RXP_FLOOD);
	cnic_reg_wr_ind(dev, BNX2_RXP_SCRATCH_RXP_FLOOD, val | (1 << 2));
}
