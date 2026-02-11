bnxt_get_ethtool_stats(struct net_device *dev,
				   struct ethtool_stats *stats, u64 *buf)
{
	u32 i, j = 0;
	struct bnxt *bp = netdev_priv(dev);
	int buf_size = bnxt_get_num_stats(bp) * sizeof(u64);
	u32 stat_fields = sizeof(struct ctx_hw_stats) / 8;

	memset(buf, 0, buf_size);

	if (!bp->bnapi)
		return;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		__le64 *hw_stats = (__le64 *)cpr->hw_stats;
		struct bnxt_sw_stats *sw_stats = &cpr->sw_stats;
		int k;

		for (k = 0; k < stat_fields; j++, k++)
			buf[j] = le64_to_cpu(hw_stats[k]);
		buf[j++] = sw_stats->rx_l4_csum_errors;
		buf[j++] = sw_stats->rx_resets;
	}
	if (bp->flags & BNXT_FLAG_PORT_STATS) {
		__le64 *port_stats = (__le64 *)bp->hw_rx_port_stats;

		for (i = 0; i < BNXT_NUM_PORT_STATS; i++, j++) {
			buf[j] = le64_to_cpu(*(port_stats +
					       bnxt_port_stats_arr[i].offset));
		}
	}
}
