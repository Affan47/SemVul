_rtl8723_dm_bt_check_wifi_state(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);

	if (rtlpriv->link_info.busytraffic) {
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_IDLE;

		if (rtlpriv->link_info.tx_busy_traffic)
			rtlpriv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_UPLINK;
		else
			rtlpriv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_UPLINK;

		if (rtlpriv->link_info.rx_busy_traffic)
			rtlpriv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_DOWNLINK;
		else
			rtlpriv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_DOWNLINK;
	} else {
		rtlpriv->btcoexist.cstate |= BT_COEX_STATE_WIFI_IDLE;
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_UPLINK;
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_DOWNLINK;
	}

	if (rtlpriv->mac80211.mode == WIRELESS_MODE_G ||
	    rtlpriv->mac80211.mode == WIRELESS_MODE_B) {
		rtlpriv->btcoexist.cstate |=
			BT_COEX_STATE_WIFI_LEGACY;
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_HT20;
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_HT40;
	} else {
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_LEGACY;
		if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) {
			rtlpriv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_HT40;
			rtlpriv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_HT20;
		} else {
			rtlpriv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_HT20;
			rtlpriv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_HT40;
		}
	}

	if (bt_operation_on)
		rtlpriv->btcoexist.cstate |= BT_COEX_STATE_BT30;
	else
		rtlpriv->btcoexist.cstate &= ~BT_COEX_STATE_BT30;
}
