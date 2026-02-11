ath10k_remove_interface(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif)
{
	struct ath10k *ar = hw->priv;
	struct ath10k_vif *arvif = ath10k_vif_to_arvif(vif);
	int ret;

	cancel_work_sync(&arvif->ap_csa_work);
	cancel_delayed_work_sync(&arvif->connection_loss_work);

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	ath10k_mac_vif_beacon_cleanup(arvif);
	spin_unlock_bh(&ar->data_lock);

	ret = ath10k_spectral_vif_stop(arvif);
	if (ret)
		ath10k_warn(ar, "failed to stop spectral for vdev %i: %d\n",
			    arvif->vdev_id, ret);

	ar->free_vdev_map |= 1LL << arvif->vdev_id;
	list_del(&arvif->list);

	if (arvif->vdev_type == WMI_VDEV_TYPE_AP ||
	    arvif->vdev_type == WMI_VDEV_TYPE_IBSS) {
		ret = ath10k_wmi_peer_delete(arvif->ar, arvif->vdev_id,
					     vif->addr);
		if (ret)
			ath10k_warn(ar, "failed to submit AP/IBSS self-peer removal on vdev %i: %d\n",
				    arvif->vdev_id, ret);

		kfree(arvif->u.ap.noa_data);
	}

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %i delete (remove interface)\n",
		   arvif->vdev_id);

	ret = ath10k_wmi_vdev_delete(ar, arvif->vdev_id);
	if (ret)
		ath10k_warn(ar, "failed to delete WMI vdev %i: %d\n",
			    arvif->vdev_id, ret);


	if (arvif->vdev_type == WMI_VDEV_TYPE_AP ||
	    arvif->vdev_type == WMI_VDEV_TYPE_IBSS) {
		ret = ath10k_wait_for_peer_deleted(ar, arvif->vdev_id,
						   vif->addr);
		if (ret)
			ath10k_warn(ar, "failed to remove AP self-peer on vdev %i: %d\n",
				    arvif->vdev_id, ret);

		spin_lock_bh(&ar->data_lock);
		ar->num_peers--;
		spin_unlock_bh(&ar->data_lock);
	}

	ath10k_peer_cleanup(ar, arvif->vdev_id);

	if (vif->type == NL80211_IFTYPE_MONITOR) {
		ar->monitor_arvif = NULL;
		ret = ath10k_monitor_recalc(ar);
		if (ret)
			ath10k_warn(ar, "failed to recalc monitor: %d\n", ret);
	}

	spin_lock_bh(&ar->htt.tx_lock);
	ath10k_mac_vif_tx_unlock_all(arvif);
	spin_unlock_bh(&ar->htt.tx_lock);

	mutex_unlock(&ar->conf_mutex);
}
