oct_cfg_adaptive_intr(struct lio *lio, struct ethtool_coalesce
				 *intr_coal, int adaptive)
{
	int ret = 0;
	struct octeon_device *oct = lio->oct_dev;
	struct oct_intrmod_cfg *intrmod_cfg;

	intrmod_cfg = &oct->intrmod;

	if (adaptive) {
		if (intr_coal->rate_sample_interval)
			intrmod_cfg->intrmod_check_intrvl =
				intr_coal->rate_sample_interval;
		else
			intrmod_cfg->intrmod_check_intrvl =
				LIO_INTRMOD_CHECK_INTERVAL;

		if (intr_coal->pkt_rate_high)
			intrmod_cfg->intrmod_maxpkt_ratethr =
				intr_coal->pkt_rate_high;
		else
			intrmod_cfg->intrmod_maxpkt_ratethr =
				LIO_INTRMOD_MAXPKT_RATETHR;

		if (intr_coal->pkt_rate_low)
			intrmod_cfg->intrmod_minpkt_ratethr =
				intr_coal->pkt_rate_low;
		else
			intrmod_cfg->intrmod_minpkt_ratethr =
				LIO_INTRMOD_MINPKT_RATETHR;

		if (intr_coal->rx_max_coalesced_frames_high)
			intrmod_cfg->intrmod_maxcnt_trigger =
				intr_coal->rx_max_coalesced_frames_high;
		else
			intrmod_cfg->intrmod_maxcnt_trigger =
				LIO_INTRMOD_MAXCNT_TRIGGER;

		if (intr_coal->rx_coalesce_usecs_high)
			intrmod_cfg->intrmod_maxtmr_trigger =
				intr_coal->rx_coalesce_usecs_high;
		else
			intrmod_cfg->intrmod_maxtmr_trigger =
				LIO_INTRMOD_MAXTMR_TRIGGER;

		if (intr_coal->rx_coalesce_usecs_low)
			intrmod_cfg->intrmod_mintmr_trigger =
				intr_coal->rx_coalesce_usecs_low;
		else
			intrmod_cfg->intrmod_mintmr_trigger =
				LIO_INTRMOD_MINTMR_TRIGGER;

		if (intr_coal->rx_max_coalesced_frames_low)
			intrmod_cfg->intrmod_mincnt_trigger =
				intr_coal->rx_max_coalesced_frames_low;
		else
			intrmod_cfg->intrmod_mincnt_trigger =
				LIO_INTRMOD_MINCNT_TRIGGER;
	}

	intrmod_cfg->intrmod_enable = adaptive;
	ret = octnet_set_intrmod_cfg(oct, intrmod_cfg);

	return ret;
}
