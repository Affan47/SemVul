_rtl92c_write_fw(struct ieee80211_hw *hw,
			     enum version_8192c version, u8 *buffer, u32 size)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool is_version_b;
	u8 *bufferptr = (u8 *)buffer;

	RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE, "FW size is %d bytes,\n", size);
	is_version_b = IS_NORMAL_CHIP(version);
	if (is_version_b) {
		u32 pageNums, remainsize;
		u32 page, offset;

		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8192CE)
			_rtl92c_fill_dummy(bufferptr, &size);

		pageNums = size / FW_8192C_PAGE_SIZE;
		remainsize = size % FW_8192C_PAGE_SIZE;

		if (pageNums > 4) {
			RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
				 "Page numbers should not greater then 4\n");
		}

		for (page = 0; page < pageNums; page++) {
			offset = page * FW_8192C_PAGE_SIZE;
			_rtl92c_fw_page_write(hw, page, (bufferptr + offset),
					      FW_8192C_PAGE_SIZE);
		}

		if (remainsize) {
			offset = pageNums * FW_8192C_PAGE_SIZE;
			page = pageNums;
			_rtl92c_fw_page_write(hw, page, (bufferptr + offset),
					      remainsize);
		}
	} else {
		_rtl92c_fw_block_write(hw, buffer, size);
	}
}
