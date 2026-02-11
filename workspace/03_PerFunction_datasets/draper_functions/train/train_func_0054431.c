bnx2x_alloc_rx_bds(struct bnx2x_fastpath *fp,
			      int rx_ring_size)
{
	struct bnx2x *bp = fp->bp;
	u16 ring_prod, cqe_ring_prod;
	int i, failure_cnt = 0;

	fp->rx_comp_cons = 0;
	cqe_ring_prod = ring_prod = 0;


	for (i = 0; i < rx_ring_size; i++) {
		if (bnx2x_alloc_rx_data(bp, fp, ring_prod, GFP_KERNEL) < 0) {
			failure_cnt++;
			continue;
		}
		ring_prod = NEXT_RX_IDX(ring_prod);
		cqe_ring_prod = NEXT_RCQ_IDX(cqe_ring_prod);
		WARN_ON(ring_prod <= (i - failure_cnt));
	}

	if (failure_cnt)
		BNX2X_ERR("was only able to allocate %d rx skbs on queue[%d]\n",
			  i - failure_cnt, fp->index);

	fp->rx_bd_prod = ring_prod;

	fp->rx_comp_prod = min_t(u16, NUM_RCQ_RINGS*RCQ_DESC_CNT,
			       cqe_ring_prod);
	fp->rx_pkt = fp->rx_calls = 0;

	bnx2x_fp_stats(bp, fp)->eth_q_stats.rx_skb_alloc_failed += failure_cnt;

	return i - failure_cnt;
}
