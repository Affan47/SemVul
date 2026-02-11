rtl8723be_dm_check_rssi_monitor(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;
	struct rtl_sta_info *drv_priv;
	u8 h2c_parameter[3] = { 0 };
	long tmp_entry_max_pwdb = 0, tmp_entry_min_pwdb = 0xff;


	spin_lock_bh(&rtlpriv->locks.entry_list_lock);
	list_for_each_entry(drv_priv, &rtlpriv->entry_list, list) {
		if (drv_priv->rssi_stat.undec_sm_pwdb <
						tmp_entry_min_pwdb)
			tmp_entry_min_pwdb =
				drv_priv->rssi_stat.undec_sm_pwdb;
		if (drv_priv->rssi_stat.undec_sm_pwdb >
						tmp_entry_max_pwdb)
			tmp_entry_max_pwdb =
				drv_priv->rssi_stat.undec_sm_pwdb;
	}
	spin_unlock_bh(&rtlpriv->locks.entry_list_lock);


	if (tmp_entry_max_pwdb != 0) {
		rtlpriv->dm.entry_max_undec_sm_pwdb =
							tmp_entry_max_pwdb;
		RTPRINT(rtlpriv, FDM, DM_PWDB,
			"EntryMaxPWDB = 0x%lx(%ld)\n",
			 tmp_entry_max_pwdb, tmp_entry_max_pwdb);
	} else {
		rtlpriv->dm.entry_max_undec_sm_pwdb = 0;
	}

	if (tmp_entry_min_pwdb != 0xff) {
		rtlpriv->dm.entry_min_undec_sm_pwdb =
							tmp_entry_min_pwdb;
		RTPRINT(rtlpriv, FDM, DM_PWDB,
			"EntryMinPWDB = 0x%lx(%ld)\n",
			 tmp_entry_min_pwdb, tmp_entry_min_pwdb);
	} else {
		rtlpriv->dm.entry_min_undec_sm_pwdb = 0;
	}

	if (rtlpriv->dm.useramask) {
		h2c_parameter[2] =
			(u8)(rtlpriv->dm.undec_sm_pwdb & 0xFF);
		h2c_parameter[1] = 0x20;
		h2c_parameter[0] = 0;
		rtl8723be_fill_h2c_cmd(hw, H2C_RSSIBE_REPORT, 3, h2c_parameter);
	} else {
		rtl_write_byte(rtlpriv, 0x4fe,
			       rtlpriv->dm.undec_sm_pwdb);
	}
	rtl8723be_dm_find_minimum_rssi(hw);
	dm_digtable->rssi_val_min =
			rtlpriv->dm_digtable.min_undec_pwdb_for_dm;
}
