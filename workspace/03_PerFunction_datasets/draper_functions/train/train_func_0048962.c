myri10ge_clean_rx_done(struct myri10ge_slice_state *ss, int budget)
{
	struct myri10ge_rx_done *rx_done = &ss->rx_done;
	struct myri10ge_priv *mgp = ss->mgp;
	unsigned long rx_bytes = 0;
	unsigned long rx_packets = 0;
	unsigned long rx_ok;
	int idx = rx_done->idx;
	int cnt = rx_done->cnt;
	int work_done = 0;
	u16 length;
	__wsum checksum;

	while (rx_done->entry[idx].length != 0 && work_done < budget) {
		length = ntohs(rx_done->entry[idx].length);
		rx_done->entry[idx].length = 0;
		checksum = csum_unfold(rx_done->entry[idx].checksum);
		rx_ok = myri10ge_rx_done(ss, length, checksum);
		rx_packets += rx_ok;
		rx_bytes += rx_ok * (unsigned long)length;
		cnt++;
		idx = cnt & (mgp->max_intr_slots - 1);
		work_done++;
	}
	rx_done->idx = idx;
	rx_done->cnt = cnt;
	ss->stats.rx_packets += rx_packets;
	ss->stats.rx_bytes += rx_bytes;


	if (ss->rx_small.fill_cnt - ss->rx_small.cnt < myri10ge_fill_thresh)
		myri10ge_alloc_rx_pages(mgp, &ss->rx_small,
					mgp->small_bytes + MXGEFW_PAD, 0);
	if (ss->rx_big.fill_cnt - ss->rx_big.cnt < myri10ge_fill_thresh)
		myri10ge_alloc_rx_pages(mgp, &ss->rx_big, mgp->big_bytes, 0);

	return work_done;
}
