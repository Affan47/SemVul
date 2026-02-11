_rtl92ee_fw_free_to_go(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int err = -EIO;
	u32 counter = 0;
	u32 value32;

	do {
		value32 = rtl_read_dword(rtlpriv, REG_MCUFWDL);
	} while ((counter++ < FW_8192C_POLLING_TIMEOUT_COUNT) &&
		 (!(value32 & FWDL_CHKSUM_RPT)));

	if (counter >= FW_8192C_POLLING_TIMEOUT_COUNT) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
			 "chksum report faill ! REG_MCUFWDL:0x%08x .\n",
			  value32);
		goto exit;
	}

	RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
		 "Checksum report OK ! REG_MCUFWDL:0x%08x .\n", value32);

	value32 = rtl_read_dword(rtlpriv, REG_MCUFWDL);
	value32 |= MCUFWDL_RDY;
	value32 &= ~WINTINI_RDY;
	rtl_write_dword(rtlpriv, REG_MCUFWDL, value32);

	rtl92ee_firmware_selfreset(hw);
	counter = 0;

	do {
		value32 = rtl_read_dword(rtlpriv, REG_MCUFWDL);
		if (value32 & WINTINI_RDY) {
			RT_TRACE(rtlpriv, COMP_FW, DBG_LOUD ,
				 "Polling FW ready success!! REG_MCUFWDL:0x%08x. count = %d\n",
				 value32, counter);
			err = 0;
			goto exit;
		}

		udelay(FW_8192C_POLLING_DELAY*10);

	} while (counter++ < FW_8192C_POLLING_TIMEOUT_COUNT);

	RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
		 "Polling FW ready fail!! REG_MCUFWDL:0x%08x. count = %d\n",
		 value32, counter);

exit:
	return err;
}
