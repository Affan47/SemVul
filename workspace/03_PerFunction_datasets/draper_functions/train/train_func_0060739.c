be_rx_stats_update(struct be_rx_obj *rxo,
			       struct be_rx_compl_info *rxcp)
{
	struct be_rx_stats *stats = rx_stats(rxo);

	u64_stats_update_begin(&stats->sync);
	stats->rx_compl++;
	stats->rx_bytes += rxcp->pkt_size;
	stats->rx_pkts++;
	if (rxcp->tunneled)
		stats->rx_vxlan_offload_pkts++;
	if (rxcp->pkt_type == BE_MULTICAST_PACKET)
		stats->rx_mcast_pkts++;
	if (rxcp->err)
		stats->rx_compl_err++;
	u64_stats_update_end(&stats->sync);
}
