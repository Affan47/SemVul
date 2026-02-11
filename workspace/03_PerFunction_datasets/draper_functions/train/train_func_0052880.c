rtl_8723e_bt_wifi_media_status_notify(struct ieee80211_hw *hw,
						bool mstatus)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 h2c_parameter[3] = {0};
	u8 chnl;

	if (!rtlpriv->btcoexist.bt_coexistence)
		return;

	if (RT_MEDIA_CONNECT == mstatus)
		h2c_parameter[0] = 0x1;
	else
		h2c_parameter[0] = 0x0;

	if (mgnt_link_status_query(hw))	{
		chnl = rtlphy->current_channel;
		h2c_parameter[1] = chnl;
	}

	if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40)
		h2c_parameter[2] = 0x30;
	else
		h2c_parameter[2] = 0x20;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		 "[BTCoex], FW write 0x19=0x%x\n",
		 h2c_parameter[0]<<16|h2c_parameter[1]<<8|h2c_parameter[2]);

	rtl8723e_fill_h2c_cmd(hw, 0x19, 3, h2c_parameter);
}
