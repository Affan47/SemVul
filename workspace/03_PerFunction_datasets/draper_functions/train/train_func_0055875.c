ath10k_mac_vif_sta_connection_loss_work(struct work_struct *work)
{
	struct ath10k_vif *arvif = container_of(work, struct ath10k_vif,
						connection_loss_work.work);
	struct ieee80211_vif *vif = arvif->vif;

	if (!arvif->is_up)
		return;

	ieee80211_connection_loss(vif);
}
