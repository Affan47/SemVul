ath5k_hw_set_antenna_mode(struct ath5k_hw *ah, u8 ant_mode)
{
	struct ieee80211_channel *channel = ah->ah_current_channel;
	bool use_def_for_tx, update_def_on_tx, use_def_for_rts, fast_div;
	bool use_def_for_sg;
	int ee_mode;
	u8 def_ant, tx_ant;
	u32 sta_id1 = 0;


	if (channel == NULL) {
		ah->ah_ant_mode = ant_mode;
		return;
	}

	def_ant = ah->ah_def_ant;

	ee_mode = ath5k_eeprom_mode_from_channel(ah, channel);

	switch (ant_mode) {
	case AR5K_ANTMODE_DEFAULT:
		tx_ant = 0;
		use_def_for_tx = false;
		update_def_on_tx = false;
		use_def_for_rts = false;
		use_def_for_sg = false;
		fast_div = true;
		break;
	case AR5K_ANTMODE_FIXED_A:
		def_ant = 1;
		tx_ant = 1;
		use_def_for_tx = true;
		update_def_on_tx = false;
		use_def_for_rts = true;
		use_def_for_sg = true;
		fast_div = false;
		break;
	case AR5K_ANTMODE_FIXED_B:
		def_ant = 2;
		tx_ant = 2;
		use_def_for_tx = true;
		update_def_on_tx = false;
		use_def_for_rts = true;
		use_def_for_sg = true;
		fast_div = false;
		break;
	case AR5K_ANTMODE_SINGLE_AP:
		def_ant = 1;
		tx_ant = 0;
		use_def_for_tx = true;
		update_def_on_tx = true;
		use_def_for_rts = true;
		use_def_for_sg = true;
		fast_div = true;
		break;
	case AR5K_ANTMODE_SECTOR_AP:
		tx_ant = 1;
		use_def_for_tx = false;
		update_def_on_tx = false;
		use_def_for_rts = true;
		use_def_for_sg = false;
		fast_div = false;
		break;
	case AR5K_ANTMODE_SECTOR_STA:
		tx_ant = 1;
		use_def_for_tx = true;
		update_def_on_tx = false;
		use_def_for_rts = true;
		use_def_for_sg = false;
		fast_div = true;
		break;
	case AR5K_ANTMODE_DEBUG:
		def_ant = 1;
		tx_ant = 2;
		use_def_for_tx = false;
		update_def_on_tx = false;
		use_def_for_rts = false;
		use_def_for_sg = false;
		fast_div = false;
		break;
	default:
		return;
	}

	ah->ah_tx_ant = tx_ant;
	ah->ah_ant_mode = ant_mode;
	ah->ah_def_ant = def_ant;

	sta_id1 |= use_def_for_tx ? AR5K_STA_ID1_DEFAULT_ANTENNA : 0;
	sta_id1 |= update_def_on_tx ? AR5K_STA_ID1_DESC_ANTENNA : 0;
	sta_id1 |= use_def_for_rts ? AR5K_STA_ID1_RTS_DEF_ANTENNA : 0;
	sta_id1 |= use_def_for_sg ? AR5K_STA_ID1_SELFGEN_DEF_ANT : 0;

	AR5K_REG_DISABLE_BITS(ah, AR5K_STA_ID1, AR5K_STA_ID1_ANTENNA_SETTINGS);

	if (sta_id1)
		AR5K_REG_ENABLE_BITS(ah, AR5K_STA_ID1, sta_id1);

	ath5k_hw_set_antenna_switch(ah, ee_mode);


	ath5k_hw_set_fast_div(ah, ee_mode, fast_div);
	ath5k_hw_set_def_antenna(ah, def_ant);
}
