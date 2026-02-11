ar9003_tx_gain_table_apply(struct ath_hw *ah)
{
	static const ath_txgain_tab modes[] = {
		ar9003_tx_gain_table_mode0,
		ar9003_tx_gain_table_mode1,
		ar9003_tx_gain_table_mode2,
		ar9003_tx_gain_table_mode3,
		ar9003_tx_gain_table_mode4,
		ar9003_tx_gain_table_mode5,
		ar9003_tx_gain_table_mode6,
		ar9003_tx_gain_table_mode7,
	};
	int idx = ar9003_hw_get_tx_gain_idx(ah);

	if (idx >= ARRAY_SIZE(modes))
		idx = 0;

	modes[idx](ah);
}
