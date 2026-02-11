_rtl8723be_c2h_content_parsing(struct ieee80211_hw *hw,
					   u8 c2h_cmd_id,
					   u8 c2h_cmd_len, u8 *tmp_buf)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	switch (c2h_cmd_id) {
	case C2H_8723B_DBG:
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "[C2H], C2H_8723BE_DBG!!\n");
		break;
	case C2H_8723B_TX_REPORT:
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "[C2H], C2H_8723BE_TX_REPORT!\n");
		break;
	case C2H_8723B_BT_INFO:
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "[C2H], C2H_8723BE_BT_INFO!!\n");
		rtlpriv->btcoexist.btc_ops->btc_btinfo_notify(rtlpriv, tmp_buf,
							      c2h_cmd_len);
		break;
	case C2H_8723B_BT_MP:
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "[C2H], C2H_8723BE_BT_MP!!\n");
		break;
	default:
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "[C2H], Unknown packet!! CmdId(%#X)!\n", c2h_cmd_id);
		break;
	}
}
