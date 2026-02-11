ath6kl_cfg80211_set_wiphy_params(struct wiphy *wiphy, u32 changed)
{
	struct ath6kl *ar = (struct ath6kl *)wiphy_priv(wiphy);
	struct ath6kl_vif *vif;
	int ret;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: changed 0x%x\n", __func__,
		   changed);

	vif = ath6kl_vif_first(ar);
	if (!vif)
		return -EIO;

	if (!ath6kl_cfg80211_ready(vif))
		return -EIO;

	if (changed & WIPHY_PARAM_RTS_THRESHOLD) {
		ret = ath6kl_wmi_set_rts_cmd(ar->wmi, wiphy->rts_threshold);
		if (ret != 0) {
			ath6kl_err("ath6kl_wmi_set_rts_cmd failed\n");
			return -EIO;
		}
	}

	return 0;
}
