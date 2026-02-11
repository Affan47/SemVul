ar5008_hw_init_txpower_ofdm(struct ath_hw *ah, int16_t *rate_array,
					int offset)
{
	int i, idx = 0;

	for (i = offset; i < offset + AR5008_OFDM_RATES; i++) {
		ah->tx_power[i] = rate_array[idx];
		idx++;
	}
}
