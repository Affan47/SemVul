ar9003_rx_gain_table_mode1(struct ath_hw *ah)
{
	if (AR_SREV_9330_12(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9331_common_wo_xlna_rx_gain_1p2);
	else if (AR_SREV_9330_11(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9331_common_wo_xlna_rx_gain_1p1);
	else if (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9340Common_wo_xlna_rx_gain_table_1p0);
	else if (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9485Common_wo_xlna_rx_gain_1_1);
	else if (AR_SREV_9462_21(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9462_2p1_common_wo_xlna_rx_gain);
	else if (AR_SREV_9462_20(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9462_2p0_common_wo_xlna_rx_gain);
	else if (AR_SREV_9550(ah)) {
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar955x_1p0_common_wo_xlna_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			ar955x_1p0_common_wo_xlna_rx_gain_bounds);
	} else if (AR_SREV_9531_10(ah) || AR_SREV_9531_11(ah)) {
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       qca953x_1p0_common_wo_xlna_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			       qca953x_1p0_common_wo_xlna_rx_gain_bounds);
	} else if (AR_SREV_9531_20(ah)) {
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       qca953x_2p0_common_wo_xlna_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			       qca953x_2p0_common_wo_xlna_rx_gain_bounds);
	} else if (AR_SREV_9561(ah)) {
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       qca956x_1p0_common_wo_xlna_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			       qca956x_1p0_common_wo_xlna_rx_gain_bounds);
	} else if (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9580_1p0_wo_xlna_rx_gain_table);
	else if (AR_SREV_9565_11(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9565_1p1_common_wo_xlna_rx_gain_table);
	else if (AR_SREV_9565(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9565_1p0_common_wo_xlna_rx_gain_table);
	else
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9300Common_wo_xlna_rx_gain_table_2p2);
}
