efuse_get_current_size(struct ieee80211_hw *hw)
{
	int continual = true;
	u16 efuse_addr = 0;
	u8 hoffset, hworden;
	u8 efuse_data, word_cnts;

	while (continual && efuse_one_byte_read(hw, efuse_addr, &efuse_data) &&
	       (efuse_addr < EFUSE_MAX_SIZE)) {
		if (efuse_data != 0xFF) {
			hoffset = (efuse_data >> 4) & 0x0F;
			hworden = efuse_data & 0x0F;
			word_cnts = efuse_calculate_word_cnts(hworden);
			efuse_addr = efuse_addr + (word_cnts * 2) + 1;
		} else {
			continual = false;
		}
	}

	return efuse_addr;
}
