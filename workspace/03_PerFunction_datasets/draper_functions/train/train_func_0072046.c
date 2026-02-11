efuse_one_byte_write(struct ieee80211_hw *hw, u16 addr, u8 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 tmpidx = 0;

	RT_TRACE(rtlpriv, COMP_EFUSE, DBG_LOUD,
		 "Addr = %x Data=%x\n", addr, data);

	rtl_write_byte(rtlpriv,
		       rtlpriv->cfg->maps[EFUSE_CTRL] + 1, (u8) (addr & 0xff));
	rtl_write_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 2,
		       (rtl_read_byte(rtlpriv,
			 rtlpriv->cfg->maps[EFUSE_CTRL] +
			 2) & 0xFC) | (u8) ((addr >> 8) & 0x03));

	rtl_write_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL], data);
	rtl_write_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 3, 0xF2);

	while ((0x80 & rtl_read_byte(rtlpriv,
				     rtlpriv->cfg->maps[EFUSE_CTRL] + 3))
	       && (tmpidx < 100)) {
		tmpidx++;
	}

	if (tmpidx < 100)
		return true;
	return false;
}
