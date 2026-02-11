iwl_mvm_prepare_mac_removal(struct iwl_mvm *mvm,
					struct ieee80211_vif *vif)
{
	u32 tfd_msk = iwl_mvm_mac_get_queues_mask(vif);

	if (tfd_msk) {


		mutex_lock(&mvm->mutex);
		iwl_mvm_flush_tx_path(mvm, tfd_msk, 0);
		mutex_unlock(&mvm->mutex);


		iwl_trans_wait_tx_queue_empty(mvm->trans, tfd_msk);
	}

	if (vif->type == NL80211_IFTYPE_P2P_DEVICE) {


		flush_work(&mvm->roc_done_wk);
	} else {


		flush_work(&mvm->sta_drained_wk);
	}
}
