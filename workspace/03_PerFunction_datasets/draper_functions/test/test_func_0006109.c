bnxt_set_coalesce(struct net_device *dev,
			     struct ethtool_coalesce *coal)
{
	struct bnxt *bp = netdev_priv(dev);
	bool update_stats = false;
	int rc = 0;

	bp->rx_coal_ticks = coal->rx_coalesce_usecs;

	bp->rx_coal_bufs = coal->rx_max_coalesced_frames * 2;
	bp->rx_coal_ticks_irq = coal->rx_coalesce_usecs_irq;
	bp->rx_coal_bufs_irq = coal->rx_max_coalesced_frames_irq * 2;

	bp->tx_coal_ticks = coal->tx_coalesce_usecs;
	bp->tx_coal_bufs = coal->tx_max_coalesced_frames;
	bp->tx_coal_ticks_irq = coal->tx_coalesce_usecs_irq;
	bp->tx_coal_bufs_irq = coal->tx_max_coalesced_frames_irq;

	if (bp->stats_coal_ticks != coal->stats_block_coalesce_usecs) {
		u32 stats_ticks = coal->stats_block_coalesce_usecs;


		if (stats_ticks)
			stats_ticks = clamp_t(u32, stats_ticks,
					      BNXT_MIN_STATS_COAL_TICKS,
					      BNXT_MAX_STATS_COAL_TICKS);
		stats_ticks = rounddown(stats_ticks, BNXT_MIN_STATS_COAL_TICKS);
		bp->stats_coal_ticks = stats_ticks;
		update_stats = true;
	}

	if (netif_running(dev)) {
		if (update_stats) {
			rc = bnxt_close_nic(bp, true, false);
			if (!rc)
				rc = bnxt_open_nic(bp, true, false);
		} else {
			rc = bnxt_hwrm_set_coal(bp);
		}
	}

	return rc;
}
