qlcnic_get_mac_stats(struct qlcnic_adapter *adapter,
		struct qlcnic_mac_statistics *mac_stats)
{
	struct qlcnic_mac_statistics_le *stats;
	struct qlcnic_cmd_args cmd;
	size_t stats_size = sizeof(struct qlcnic_mac_statistics_le);
	dma_addr_t stats_dma_t;
	void *stats_addr;
	int err;

	if (mac_stats == NULL)
		return -ENOMEM;

	stats_addr = dma_zalloc_coherent(&adapter->pdev->dev, stats_size,
					 &stats_dma_t, GFP_KERNEL);
	if (!stats_addr)
		return -ENOMEM;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_MAC_STATS);
	if (err)
		goto out_free_dma;

	cmd.req.arg[1] = stats_size << 16;
	cmd.req.arg[2] = MSD(stats_dma_t);
	cmd.req.arg[3] = LSD(stats_dma_t);
	err = qlcnic_issue_cmd(adapter, &cmd);
	if (!err) {
		stats = stats_addr;
		mac_stats->mac_tx_frames = le64_to_cpu(stats->mac_tx_frames);
		mac_stats->mac_tx_bytes = le64_to_cpu(stats->mac_tx_bytes);
		mac_stats->mac_tx_mcast_pkts =
					le64_to_cpu(stats->mac_tx_mcast_pkts);
		mac_stats->mac_tx_bcast_pkts =
					le64_to_cpu(stats->mac_tx_bcast_pkts);
		mac_stats->mac_rx_frames = le64_to_cpu(stats->mac_rx_frames);
		mac_stats->mac_rx_bytes = le64_to_cpu(stats->mac_rx_bytes);
		mac_stats->mac_rx_mcast_pkts =
					le64_to_cpu(stats->mac_rx_mcast_pkts);
		mac_stats->mac_rx_length_error =
				le64_to_cpu(stats->mac_rx_length_error);
		mac_stats->mac_rx_length_small =
				le64_to_cpu(stats->mac_rx_length_small);
		mac_stats->mac_rx_length_large =
				le64_to_cpu(stats->mac_rx_length_large);
		mac_stats->mac_rx_jabber = le64_to_cpu(stats->mac_rx_jabber);
		mac_stats->mac_rx_dropped = le64_to_cpu(stats->mac_rx_dropped);
		mac_stats->mac_rx_crc_error = le64_to_cpu(stats->mac_rx_crc_error);
	} else {
		dev_err(&adapter->pdev->dev,
			"%s: Get mac stats failed, err=%d.\n", __func__, err);
	}

	qlcnic_free_mbx_args(&cmd);

out_free_dma:
	dma_free_coherent(&adapter->pdev->dev, stats_size, stats_addr,
			  stats_dma_t);

	return err;
}
