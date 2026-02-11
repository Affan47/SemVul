ath10k_mac_tx_wmi_mgmt(struct ath10k *ar, struct sk_buff *skb)
{
	struct sk_buff_head *q = &ar->wmi_mgmt_tx_queue;
	int ret = 0;

	spin_lock_bh(&ar->data_lock);

	if (skb_queue_len(q) == ATH10K_MAX_NUM_MGMT_PENDING) {
		ath10k_warn(ar, "wmi mgmt tx queue is full\n");
		ret = -ENOSPC;
		goto unlock;
	}

	__skb_queue_tail(q, skb);
	ieee80211_queue_work(ar->hw, &ar->wmi_mgmt_tx_work);

unlock:
	spin_unlock_bh(&ar->data_lock);

	return ret;
}
