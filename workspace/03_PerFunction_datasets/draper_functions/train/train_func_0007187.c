_rtl8821ae_mrate_idx_to_arfr_id(
	struct ieee80211_hw *hw, u8 rate_index,
	enum wireless_mode wirelessmode)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 ret = 0;
	switch (rate_index) {
	case RATR_INX_WIRELESS_NGB:
		if (rtlphy->rf_type == RF_1T1R)
			ret = 1;
		else
			ret = 0;
		; break;
	case RATR_INX_WIRELESS_N:
	case RATR_INX_WIRELESS_NG:
		if (rtlphy->rf_type == RF_1T1R)
			ret = 5;
		else
			ret = 4;
		; break;
	case RATR_INX_WIRELESS_NB:
		if (rtlphy->rf_type == RF_1T1R)
			ret = 3;
		else
			ret = 2;
		; break;
	case RATR_INX_WIRELESS_GB:
		ret = 6;
		break;
	case RATR_INX_WIRELESS_G:
		ret = 7;
		break;
	case RATR_INX_WIRELESS_B:
		ret = 8;
		break;
	case RATR_INX_WIRELESS_MC:
		if ((wirelessmode == WIRELESS_MODE_B)
			|| (wirelessmode == WIRELESS_MODE_G)
			|| (wirelessmode == WIRELESS_MODE_N_24G)
			|| (wirelessmode == WIRELESS_MODE_AC_24G))
			ret = 6;
		else
			ret = 7;
	case RATR_INX_WIRELESS_AC_5N:
		if (rtlphy->rf_type == RF_1T1R)
			ret = 10;
		else
			ret = 9;
		break;
	case RATR_INX_WIRELESS_AC_24N:
		if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80) {
			if (rtlphy->rf_type == RF_1T1R)
				ret = 10;
			else
				ret = 9;
		} else {
			if (rtlphy->rf_type == RF_1T1R)
				ret = 11;
			else
				ret = 12;
		}
		break;
	default:
		ret = 0; break;
	}
	return ret;
}
