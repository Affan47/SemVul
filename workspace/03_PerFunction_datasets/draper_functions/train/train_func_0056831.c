rtl92c_dm_ctrl_initgain_by_rssi(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *digtable = &rtlpriv->dm_digtable;
	u32 isbt;


	if (rtlpriv->falsealm_cnt.cnt_all > 10000) {
		digtable->large_fa_hit++;
		if (digtable->forbidden_igi < digtable->cur_igvalue) {
			digtable->forbidden_igi = digtable->cur_igvalue;
			digtable->large_fa_hit = 1;
		}

		if (digtable->large_fa_hit >= 3) {
			if ((digtable->forbidden_igi + 1) >
			    digtable->rx_gain_max)
				digtable->rx_gain_min = digtable->rx_gain_max;
			else
				digtable->rx_gain_min = (digtable->forbidden_igi + 1);
			digtable->recover_cnt = 3600;
		}
	} else {

		if (digtable->recover_cnt != 0) {
			digtable->recover_cnt--;
		} else {
			if (digtable->large_fa_hit == 0) {
				if ((digtable->forbidden_igi-1) < DM_DIG_MIN) {
					digtable->forbidden_igi = DM_DIG_MIN;
					digtable->rx_gain_min = DM_DIG_MIN;
				} else {
					digtable->forbidden_igi--;
					digtable->rx_gain_min = digtable->forbidden_igi + 1;
				}
			} else if (digtable->large_fa_hit == 3) {
				digtable->large_fa_hit = 0;
			}
		}
	}
	if (rtlpriv->falsealm_cnt.cnt_all < 250) {
		isbt = rtl_read_byte(rtlpriv, 0x4fd) & 0x01;

		if (!isbt) {
			if (rtlpriv->falsealm_cnt.cnt_all >
			    digtable->fa_lowthresh) {
				if ((digtable->back_val - 2) <
				   digtable->back_range_min)
					digtable->back_val = digtable->back_range_min;
				else
					digtable->back_val -= 2;
			} else if (rtlpriv->falsealm_cnt.cnt_all <
				   digtable->fa_lowthresh) {
				if ((digtable->back_val + 2) >
				    digtable->back_range_max)
					digtable->back_val = digtable->back_range_max;
				else
					digtable->back_val += 2;
			}
		} else {
			digtable->back_val = DM_DIG_BACKOFF_DEFAULT;
		}
	} else {

		if (rtlpriv->falsealm_cnt.cnt_all > 1000)
			digtable->cur_igvalue = digtable->pre_igvalue + 2;
		else if (rtlpriv->falsealm_cnt.cnt_all > 750)
			digtable->cur_igvalue = digtable->pre_igvalue + 1;
		else if (rtlpriv->falsealm_cnt.cnt_all < 500)
			digtable->cur_igvalue = digtable->pre_igvalue - 1;
	}


	if (digtable->cur_igvalue > digtable->rx_gain_max)
		digtable->cur_igvalue = digtable->rx_gain_max;

	if (digtable->cur_igvalue < digtable->rx_gain_min)
		digtable->cur_igvalue = digtable->rx_gain_min;

	rtl92c_dm_write_dig(hw);
}
