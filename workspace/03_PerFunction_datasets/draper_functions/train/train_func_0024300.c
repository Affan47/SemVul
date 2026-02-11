mwifiex_init_lock_list(struct mwifiex_adapter *adapter)
{
	struct mwifiex_private *priv;
	s32 i, j;

	spin_lock_init(&adapter->mwifiex_lock);
	spin_lock_init(&adapter->int_lock);
	spin_lock_init(&adapter->main_proc_lock);
	spin_lock_init(&adapter->mwifiex_cmd_lock);
	spin_lock_init(&adapter->queue_lock);
	for (i = 0; i < adapter->priv_num; i++) {
		if (adapter->priv[i]) {
			priv = adapter->priv[i];
			spin_lock_init(&priv->rx_pkt_lock);
			spin_lock_init(&priv->wmm.ra_list_spinlock);
			spin_lock_init(&priv->curr_bcn_buf_lock);
			spin_lock_init(&priv->sta_list_spinlock);
			spin_lock_init(&priv->auto_tdls_lock);
		}
	}


	INIT_LIST_HEAD(&adapter->cmd_free_q);

	INIT_LIST_HEAD(&adapter->cmd_pending_q);

	INIT_LIST_HEAD(&adapter->scan_pending_q);

	spin_lock_init(&adapter->cmd_free_q_lock);
	spin_lock_init(&adapter->cmd_pending_q_lock);
	spin_lock_init(&adapter->scan_pending_q_lock);
	spin_lock_init(&adapter->rx_proc_lock);

	skb_queue_head_init(&adapter->rx_data_q);
	skb_queue_head_init(&adapter->tx_data_q);

	for (i = 0; i < adapter->priv_num; ++i) {
		INIT_LIST_HEAD(&adapter->bss_prio_tbl[i].bss_prio_head);
		spin_lock_init(&adapter->bss_prio_tbl[i].bss_prio_lock);
	}

	for (i = 0; i < adapter->priv_num; i++) {
		if (!adapter->priv[i])
			continue;
		priv = adapter->priv[i];
		for (j = 0; j < MAX_NUM_TID; ++j)
			INIT_LIST_HEAD(&priv->wmm.tid_tbl_ptr[j].ra_list);
		INIT_LIST_HEAD(&priv->tx_ba_stream_tbl_ptr);
		INIT_LIST_HEAD(&priv->rx_reorder_tbl_ptr);
		INIT_LIST_HEAD(&priv->sta_list);
		INIT_LIST_HEAD(&priv->auto_tdls_list);
		skb_queue_head_init(&priv->tdls_txq);
		skb_queue_head_init(&priv->bypass_txq);

		spin_lock_init(&priv->tx_ba_stream_tbl_lock);
		spin_lock_init(&priv->rx_reorder_tbl_lock);

		spin_lock_init(&priv->ack_status_lock);
		idr_init(&priv->ack_status_frames);
	}

	return 0;
}
