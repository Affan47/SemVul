ar9003_rx_gain_table_mode3(struct ath_hw *ah)
{
	if (AR_SREV_9462_21(ah)) {
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9462_2p1_common_5g_xlna_only_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_xlna,
			       ar9462_2p1_baseband_postamble_5g_xlna);
	} else if (AR_SREV_9462_20(ah)) {
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9462_2p0_common_5g_xlna_only_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_xlna,
			       ar9462_2p0_baseband_postamble_5g_xlna);
	}
}
