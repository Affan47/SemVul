bnx2x_set_eee(struct net_device *dev, struct ethtool_eee *edata)
{
	struct bnx2x *bp = netdev_priv(dev);
	u32 eee_cfg;
	u32 advertised;

	if (IS_MF(bp))
		return 0;

	if (!SHMEM2_HAS(bp, eee_status[BP_PORT(bp)])) {
		DP(BNX2X_MSG_ETHTOOL, "BC Version does not support EEE\n");
		return -EOPNOTSUPP;
	}

	eee_cfg = bp->link_vars.eee_status;

	if (!(eee_cfg & SHMEM_EEE_SUPPORTED_MASK)) {
		DP(BNX2X_MSG_ETHTOOL, "Board does not support EEE!\n");
		return -EOPNOTSUPP;
	}

	advertised = bnx2x_adv_to_eee(edata->advertised,
				      SHMEM_EEE_ADV_STATUS_SHIFT);
	if ((advertised != (eee_cfg & SHMEM_EEE_ADV_STATUS_MASK))) {
		DP(BNX2X_MSG_ETHTOOL,
		   "Direct manipulation of EEE advertisement is not supported\n");
		return -EINVAL;
	}

	if (edata->tx_lpi_timer > EEE_MODE_TIMER_MASK) {
		DP(BNX2X_MSG_ETHTOOL,
		   "Maximal Tx Lpi timer supported is %x(u)\n",
		   EEE_MODE_TIMER_MASK);
		return -EINVAL;
	}
	if (edata->tx_lpi_enabled &&
	    (edata->tx_lpi_timer < EEE_MODE_NVRAM_AGGRESSIVE_TIME)) {
		DP(BNX2X_MSG_ETHTOOL,
		   "Minimal Tx Lpi timer supported is %d(u)\n",
		   EEE_MODE_NVRAM_AGGRESSIVE_TIME);
		return -EINVAL;
	}


	if (edata->eee_enabled)
		bp->link_params.eee_mode |= EEE_MODE_ADV_LPI;
	else
		bp->link_params.eee_mode &= ~EEE_MODE_ADV_LPI;

	if (edata->tx_lpi_enabled)
		bp->link_params.eee_mode |= EEE_MODE_ENABLE_LPI;
	else
		bp->link_params.eee_mode &= ~EEE_MODE_ENABLE_LPI;

	bp->link_params.eee_mode &= ~EEE_MODE_TIMER_MASK;
	bp->link_params.eee_mode |= (edata->tx_lpi_timer &
				    EEE_MODE_TIMER_MASK) |
				    EEE_MODE_OVERRIDE_NVRAM |
				    EEE_MODE_OUTPUT_TIME;


	if (netif_running(dev)) {
		bnx2x_stats_handle(bp, STATS_EVENT_STOP);
		bnx2x_force_link_reset(bp);
		bnx2x_link_set(bp);
	}

	return 0;
}
