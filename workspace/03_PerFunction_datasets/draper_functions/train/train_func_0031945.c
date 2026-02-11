process_single_down_tx_qlock(struct drm_dp_mst_topology_mgr *mgr)
{
	struct drm_dp_sideband_msg_tx *txmsg;
	int ret;

	WARN_ON(!mutex_is_locked(&mgr->qlock));


	if (list_empty(&mgr->tx_msg_downq)) {
		mgr->tx_down_in_progress = false;
		return;
	}
	mgr->tx_down_in_progress = true;

	txmsg = list_first_entry(&mgr->tx_msg_downq, struct drm_dp_sideband_msg_tx, next);
	ret = process_single_tx_qlock(mgr, txmsg, false);
	if (ret == 1) {

		list_del(&txmsg->next);
	} else if (ret) {
		DRM_DEBUG_KMS("failed to send msg in q %d\n", ret);
		list_del(&txmsg->next);
		if (txmsg->seqno != -1)
			txmsg->dst->tx_slots[txmsg->seqno] = NULL;
		txmsg->state = DRM_DP_SIDEBAND_TX_TIMEOUT;
		wake_up(&mgr->tx_waitq);
	}
	if (list_empty(&mgr->tx_msg_downq)) {
		mgr->tx_down_in_progress = false;
		return;
	}
}
