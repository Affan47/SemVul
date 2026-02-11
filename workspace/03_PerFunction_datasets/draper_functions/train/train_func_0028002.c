rtl92ee_firmware_selfreset(struct ieee80211_hw *hw)
{
	u8 u1b_tmp;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	u1b_tmp = rtl_read_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_write_byte(rtlpriv, REG_RSV_CTRL + 1, (u1b_tmp & (~BIT(0))));

	u1b_tmp = rtl_read_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN + 1, (u1b_tmp & (~BIT(2))));

	udelay(50);

	u1b_tmp = rtl_read_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_write_byte(rtlpriv, REG_RSV_CTRL + 1, (u1b_tmp | BIT(0)));

	u1b_tmp = rtl_read_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN + 1, (u1b_tmp | BIT(2)));

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD ,
		 "  _8051Reset92E(): 8051 reset success .\n");
}
