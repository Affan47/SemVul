_rtl88e_check_condition(struct ieee80211_hw *hw,
				    const u32  condition)
{
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 _board = rtlefuse->board_type;
	u32 _interface = rtlhal->interface;
	u32 _platform = 0x08;
	u32 cond = condition;

	if (condition == 0xCDCDCDCD)
		return true;

	cond = condition & 0xFF;
	if ((_board & cond) == 0 && cond != 0x1F)
		return false;

	cond = condition & 0xFF00;
	cond = cond >> 8;
	if ((_interface & cond) == 0 && cond != 0x07)
		return false;

	cond = condition & 0xFF0000;
	cond = cond >> 16;
	if ((_platform & cond) == 0 && cond != 0x0F)
		return false;
	return true;
}
