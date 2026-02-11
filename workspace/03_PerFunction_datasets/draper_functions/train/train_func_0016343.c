rtl_op_sta_remove(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif,
				struct ieee80211_sta *sta)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_sta_info *sta_entry;
	if (sta) {
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
			 "Remove sta addr is %pM\n", sta->addr);
		sta_entry = (struct rtl_sta_info *)sta->drv_priv;
		sta_entry->wireless_mode = 0;
		sta_entry->ratr_index = 0;
		spin_lock_bh(&rtlpriv->locks.entry_list_lock);
		list_del(&sta_entry->list);
		spin_unlock_bh(&rtlpriv->locks.entry_list_lock);
	}
	return 0;
}
