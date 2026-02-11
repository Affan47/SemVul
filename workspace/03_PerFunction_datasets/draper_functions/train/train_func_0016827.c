mwifiex_cancel_pending_ioctl(struct mwifiex_adapter *adapter)
{
	struct cmd_ctrl_node *cmd_node = NULL, *tmp_node = NULL;
	unsigned long cmd_flags;
	unsigned long scan_pending_q_flags;
	struct mwifiex_private *priv;
	int i;

	if ((adapter->curr_cmd) &&
	    (adapter->curr_cmd->wait_q_enabled)) {
		spin_lock_irqsave(&adapter->mwifiex_cmd_lock, cmd_flags);
		cmd_node = adapter->curr_cmd;


		adapter->curr_cmd = NULL;
		spin_unlock_irqrestore(&adapter->mwifiex_cmd_lock, cmd_flags);

		mwifiex_recycle_cmd_node(adapter, cmd_node);
	}


	spin_lock_irqsave(&adapter->scan_pending_q_lock,
			  scan_pending_q_flags);
	list_for_each_entry_safe(cmd_node, tmp_node,
				 &adapter->scan_pending_q, list) {
		list_del(&cmd_node->list);
		cmd_node->wait_q_enabled = false;
		mwifiex_insert_cmd_to_free_q(adapter, cmd_node);
	}
	spin_unlock_irqrestore(&adapter->scan_pending_q_lock,
			       scan_pending_q_flags);

	if (adapter->scan_processing) {
		spin_lock_irqsave(&adapter->mwifiex_cmd_lock, cmd_flags);
		adapter->scan_processing = false;
		spin_unlock_irqrestore(&adapter->mwifiex_cmd_lock, cmd_flags);
		for (i = 0; i < adapter->priv_num; i++) {
			priv = adapter->priv[i];
			if (!priv)
				continue;
			if (priv->scan_request) {
				mwifiex_dbg(adapter, WARN, "info: aborting scan\n");
				cfg80211_scan_done(priv->scan_request, 1);
				priv->scan_request = NULL;
			}
		}
	}
}
