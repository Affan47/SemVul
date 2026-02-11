efuse_pg_packet_write(struct ieee80211_hw *hw,
				 u8 offset, u8 word_en, u8 *data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct pgpkt_struct target_pkt;
	u8 write_state = PG_STATE_HEADER;
	int continual = true, dataempty = true, result = true;
	u16 efuse_addr = 0;
	u8 efuse_data;
	u8 target_word_cnts = 0;
	u8 badworden = 0x0F;
	static int repeat_times;

	if (efuse_get_current_size(hw) >= (EFUSE_MAX_SIZE -
		rtlpriv->cfg->maps[EFUSE_OOB_PROTECT_BYTES_LEN])) {
		RTPRINT(rtlpriv, FEEPROM, EFUSE_PG,
			"efuse_pg_packet_write error\n");
		return false;
	}

	target_pkt.offset = offset;
	target_pkt.word_en = word_en;

	memset(target_pkt.data, 0xFF,  8 * sizeof(u8));

	efuse_word_enable_data_read(word_en, data, target_pkt.data);
	target_word_cnts = efuse_calculate_word_cnts(target_pkt.word_en);

	RTPRINT(rtlpriv, FEEPROM, EFUSE_PG, "efuse Power ON\n");

	while (continual && (efuse_addr < (EFUSE_MAX_SIZE -
		rtlpriv->cfg->maps[EFUSE_OOB_PROTECT_BYTES_LEN]))) {

		if (write_state == PG_STATE_HEADER) {
			dataempty = true;
			badworden = 0x0F;
			RTPRINT(rtlpriv, FEEPROM, EFUSE_PG,
				"efuse PG_STATE_HEADER\n");

			if (efuse_one_byte_read(hw, efuse_addr, &efuse_data) &&
			    (efuse_data != 0xFF))
				efuse_write_data_case1(hw, &efuse_addr,
						       efuse_data, offset,
						       &continual,
						       &write_state,
						       &target_pkt,
						       &repeat_times, &result,
						       word_en);
			else
				efuse_write_data_case2(hw, &efuse_addr,
						       &continual,
						       &write_state,
						       target_pkt,
						       &repeat_times,
						       &result);

		} else if (write_state == PG_STATE_DATA) {
			RTPRINT(rtlpriv, FEEPROM, EFUSE_PG,
				"efuse PG_STATE_DATA\n");
			badworden = 0x0f;
			badworden =
			    enable_efuse_data_write(hw, efuse_addr + 1,
						    target_pkt.word_en,
						    target_pkt.data);

			if ((badworden & 0x0F) == 0x0F) {
				continual = false;
			} else {
				efuse_addr =
				    efuse_addr + (2 * target_word_cnts) + 1;

				target_pkt.offset = offset;
				target_pkt.word_en = badworden;
				target_word_cnts =
				    efuse_calculate_word_cnts(target_pkt.
							      word_en);
				write_state = PG_STATE_HEADER;
				repeat_times++;
				if (repeat_times > EFUSE_REPEAT_THRESHOLD_) {
					continual = false;
					result = false;
				}
				RTPRINT(rtlpriv, FEEPROM, EFUSE_PG,
					"efuse PG_STATE_HEADER-3\n");
			}
		}
	}

	if (efuse_addr >= (EFUSE_MAX_SIZE -
		rtlpriv->cfg->maps[EFUSE_OOB_PROTECT_BYTES_LEN])) {
		RT_TRACE(rtlpriv, COMP_EFUSE, DBG_LOUD,
			 "efuse_addr(%#x) Out of size!!\n", efuse_addr);
	}

	return true;
}
