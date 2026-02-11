bnxt_get_stats64(struct net_device *dev, struct rtnl_link_stats64 *stats)
{
	u32 i;
	struct bnxt *bp = netdev_priv(dev);

	memset(stats, 0, sizeof(struct rtnl_link_stats64));

	if (!bp->bnapi)
		return stats;


	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		struct ctx_hw_stats *hw_stats = cpr->hw_stats;

		stats->rx_packets += le64_to_cpu(hw_stats->rx_ucast_pkts);
		stats->rx_packets += le64_to_cpu(hw_stats->rx_mcast_pkts);
		stats->rx_packets += le64_to_cpu(hw_stats->rx_bcast_pkts);

		stats->tx_packets += le64_to_cpu(hw_stats->tx_ucast_pkts);
		stats->tx_packets += le64_to_cpu(hw_stats->tx_mcast_pkts);
		stats->tx_packets += le64_to_cpu(hw_stats->tx_bcast_pkts);

		stats->rx_bytes += le64_to_cpu(hw_stats->rx_ucast_bytes);
		stats->rx_bytes += le64_to_cpu(hw_stats->rx_mcast_bytes);
		stats->rx_bytes += le64_to_cpu(hw_stats->rx_bcast_bytes);

		stats->tx_bytes += le64_to_cpu(hw_stats->tx_ucast_bytes);
		stats->tx_bytes += le64_to_cpu(hw_stats->tx_mcast_bytes);
		stats->tx_bytes += le64_to_cpu(hw_stats->tx_bcast_bytes);

		stats->rx_missed_errors +=
			le64_to_cpu(hw_stats->rx_discard_pkts);

		stats->multicast += le64_to_cpu(hw_stats->rx_mcast_pkts);

		stats->rx_dropped += le64_to_cpu(hw_stats->rx_drop_pkts);

		stats->tx_dropped += le64_to_cpu(hw_stats->tx_drop_pkts);
	}

	return stats;
}
