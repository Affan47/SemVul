wlc_phy_txpower_sromlimit_get_nphy(struct brcms_phy *pi, uint chan, u8 *max_pwr,
				   u8 txp_rate_idx)
{
	u8 chan_freq_range;

	chan_freq_range = wlc_phy_get_chan_freq_range_nphy(pi, chan);
	switch (chan_freq_range) {
	case WL_CHAN_FREQ_RANGE_2G:
		*max_pwr = pi->tx_srom_max_rate_2g[txp_rate_idx];
		break;
	case WL_CHAN_FREQ_RANGE_5GM:
		*max_pwr = pi->tx_srom_max_rate_5g_mid[txp_rate_idx];
		break;
	case WL_CHAN_FREQ_RANGE_5GL:
		*max_pwr = pi->tx_srom_max_rate_5g_low[txp_rate_idx];
		break;
	case WL_CHAN_FREQ_RANGE_5GH:
		*max_pwr = pi->tx_srom_max_rate_5g_hi[txp_rate_idx];
		break;
	default:
		*max_pwr = pi->tx_srom_max_rate_2g[txp_rate_idx];
		break;
	}

	return;
}
