rtl8723e_dm_bt_need_to_dec_bt_pwr(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (mgnt_link_status_query(hw) == RT_MEDIA_CONNECT) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"Need to decrease bt power\n");
			rtlpriv->btcoexist.cstate |=
			BT_COEX_STATE_DEC_BT_POWER;
			return true;
	}

	rtlpriv->btcoexist.cstate &= ~BT_COEX_STATE_DEC_BT_POWER;
	return false;
}
