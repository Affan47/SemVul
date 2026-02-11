ath10k_mac_op_unassign_vif_chanctx(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   struct ieee80211_chanctx_conf *ctx)
{
	struct ath10k *ar = hw->priv;
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	int ret;

	mutex_lock(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac chanctx unassign ptr %p vdev_id %i\n",
		   ctx, arvif->vdev_id);

	WARN_ON(!arvif->is_started);

	if (vif->type == NL80211_IFTYPE_MONITOR) {
		WARN_ON(!arvif->is_up);

		ret = ath10k_wmi_vdev_down(ar, arvif->vdev_id);
		if (ret)
			ath10k_warn(ar, "failed to down monitor vdev %i: %d\n",
				    arvif->vdev_id, ret);

		arvif->is_up = false;
	}

	ret = ath10k_vdev_stop(arvif);
	if (ret)
		ath10k_warn(ar, "failed to stop vdev %i: %d\n",
			    arvif->vdev_id, ret);

	arvif->is_started = false;

	mutex_unlock(&ar->conf_mutex);
}
