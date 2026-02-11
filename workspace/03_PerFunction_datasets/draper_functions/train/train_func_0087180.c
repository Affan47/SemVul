iwl_mvm_disable_txq(struct iwl_mvm *mvm, int queue, int mac80211_queue,
			 u8 tid, u8 flags)
{
	struct iwl_scd_txq_cfg_cmd cmd = {
		.scd_queue = queue,
		.enable = 0,
	};
	bool remove_mac_queue = true;
	int ret;

	spin_lock_bh(&mvm->queue_info_lock);

	if (WARN_ON(mvm->queue_info[queue].hw_queue_refcount == 0)) {
		spin_unlock_bh(&mvm->queue_info_lock);
		return;
	}

	mvm->queue_info[queue].tid_bitmap &= ~BIT(tid);


	if (tid < IWL_MAX_TID_COUNT) {
		unsigned long tid_bitmap =
			mvm->queue_info[queue].tid_bitmap;
		int ac = tid_to_mac80211_ac[tid];
		int i;

		for_each_set_bit(i, &tid_bitmap, IWL_MAX_TID_COUNT) {
			if (tid_to_mac80211_ac[i] == ac)
				remove_mac_queue = false;
		}
	}

	if (remove_mac_queue)
		mvm->queue_info[queue].hw_queue_to_mac80211 &=
			~BIT(mac80211_queue);
	mvm->queue_info[queue].hw_queue_refcount--;

	cmd.enable = mvm->queue_info[queue].hw_queue_refcount ? 1 : 0;

	IWL_DEBUG_TX_QUEUES(mvm,
			    "Disabling TXQ #%d refcount=%d (mac80211 map:0x%x)\n",
			    queue,
			    mvm->queue_info[queue].hw_queue_refcount,
			    mvm->queue_info[queue].hw_queue_to_mac80211);


	if (cmd.enable) {
		spin_unlock_bh(&mvm->queue_info_lock);
		return;
	}


	WARN(mvm->queue_info[queue].hw_queue_refcount ||
	     mvm->queue_info[queue].tid_bitmap ||
	     mvm->queue_info[queue].hw_queue_to_mac80211,
	     "TXQ #%d info out-of-sync - refcount=%d, mac map=0x%x, tid=0x%x\n",
	     queue, mvm->queue_info[queue].hw_queue_refcount,
	     mvm->queue_info[queue].hw_queue_to_mac80211,
	     mvm->queue_info[queue].tid_bitmap);


	mvm->queue_info[queue].hw_queue_refcount = 0;
	mvm->queue_info[queue].tid_bitmap = 0;
	mvm->queue_info[queue].hw_queue_to_mac80211 = 0;

	spin_unlock_bh(&mvm->queue_info_lock);

	iwl_trans_txq_disable(mvm->trans, queue, false);
	ret = iwl_mvm_send_cmd_pdu(mvm, SCD_QUEUE_CFG, flags,
				   sizeof(cmd), &cmd);
	if (ret)
		IWL_ERR(mvm, "Failed to disable queue %d (ret=%d)\n",
			queue, ret);
}
