ath10k_reg_notifier(struct wiphy *wiphy,
				struct regulatory_request *request)
{
	struct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	struct ath10k *ar = hw->priv;
	bool result;

	ath_reg_notifier_apply(wiphy, request, &ar->ath_common.regulatory);

	if (config_enabled(CONFIG_ATH10K_DFS_CERTIFIED) && ar->dfs_detector) {
		ath10k_dbg(ar, ATH10K_DBG_REGULATORY, "dfs region 0x%x\n",
			   request->dfs_region);
		result = ar->dfs_detector->set_dfs_domain(ar->dfs_detector,
							  request->dfs_region);
		if (!result)
			ath10k_warn(ar, "DFS region 0x%X not supported, will trigger radar for every pulse\n",
				    request->dfs_region);
	}

	mutex_lock(&ar->conf_mutex);
	if (ar->state == ATH10K_STATE_ON)
		ath10k_regd_update(ar);
	mutex_unlock(&ar->conf_mutex);
}
