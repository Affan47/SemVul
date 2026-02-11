ar9003_hw_init_txpower_ht(struct ath_hw *ah, u8 *rate_array,
				      int ss_offset, int ds_offset,
				      int ts_offset, bool is_40)
{
	int i, j, mcs_idx = 0;
	const u8 *mcs2pwr = (is_40) ? mcs2pwr_ht40 : mcs2pwr_ht20;

	for (i = ss_offset; i < ss_offset + AR9300_HT_SS_RATES; i++) {
		j = mcs2pwr[mcs_idx];
		ah->tx_power[i] = rate_array[j];
		mcs_idx++;
	}

	for (i = ds_offset; i < ds_offset + AR9300_HT_DS_RATES; i++) {
		j = mcs2pwr[mcs_idx];
		ah->tx_power[i] = rate_array[j];
		mcs_idx++;
	}

	for (i = ts_offset; i < ts_offset + AR9300_HT_TS_RATES; i++) {
		j = mcs2pwr[mcs_idx];
		ah->tx_power[i] = rate_array[j];
		mcs_idx++;
	}
}
