mwifiex_scan_networks(struct mwifiex_private *priv,
			  const struct mwifiex_user_scan_cfg *user_scan_in)
{
	int ret;
	struct mwifiex_adapter *adapter = priv->adapter;
	struct cmd_ctrl_node *cmd_node;
	union mwifiex_scan_cmd_config_tlv *scan_cfg_out;
	struct mwifiex_ie_types_chan_list_param_set *chan_list_out;
	struct mwifiex_chan_scan_param_set *scan_chan_list;
	u8 filtered_scan;
	u8 scan_current_chan_only;
	u8 max_chan_per_scan;
	unsigned long flags;

	if (adapter->scan_processing) {
		mwifiex_dbg(adapter, WARN,
			    "cmd: Scan already in process...\n");
		return -EBUSY;
	}

	if (priv->scan_block) {
		mwifiex_dbg(adapter, WARN,
			    "cmd: Scan is blocked during association...\n");
		return -EBUSY;
	}

	if (adapter->surprise_removed || adapter->is_cmd_timedout) {
		mwifiex_dbg(adapter, ERROR,
			    "Ignore scan. Card removed or firmware in bad state\n");
		return -EFAULT;
	}

	spin_lock_irqsave(&adapter->mwifiex_cmd_lock, flags);
	adapter->scan_processing = true;
	spin_unlock_irqrestore(&adapter->mwifiex_cmd_lock, flags);

	scan_cfg_out = kzalloc(sizeof(union mwifiex_scan_cmd_config_tlv),
			       GFP_KERNEL);
	if (!scan_cfg_out) {
		ret = -ENOMEM;
		goto done;
	}

	scan_chan_list = kcalloc(MWIFIEX_USER_SCAN_CHAN_MAX,
				 sizeof(struct mwifiex_chan_scan_param_set),
				 GFP_KERNEL);
	if (!scan_chan_list) {
		kfree(scan_cfg_out);
		ret = -ENOMEM;
		goto done;
	}

	mwifiex_config_scan(priv, user_scan_in, &scan_cfg_out->config,
			    &chan_list_out, scan_chan_list, &max_chan_per_scan,
			    &filtered_scan, &scan_current_chan_only);

	ret = mwifiex_scan_channel_list(priv, max_chan_per_scan, filtered_scan,
					&scan_cfg_out->config, chan_list_out,
					scan_chan_list);


	if (!ret) {
		spin_lock_irqsave(&adapter->scan_pending_q_lock, flags);
		if (!list_empty(&adapter->scan_pending_q)) {
			cmd_node = list_first_entry(&adapter->scan_pending_q,
						    struct cmd_ctrl_node, list);
			list_del(&cmd_node->list);
			spin_unlock_irqrestore(&adapter->scan_pending_q_lock,
					       flags);
			mwifiex_insert_cmd_to_pending_q(adapter, cmd_node,
							true);
			queue_work(adapter->workqueue, &adapter->main_work);


			if (!priv->scan_request) {
				mwifiex_dbg(adapter, INFO,
					    "wait internal scan\n");
				mwifiex_wait_queue_complete(adapter, cmd_node);
			}
		} else {
			spin_unlock_irqrestore(&adapter->scan_pending_q_lock,
					       flags);
		}
	}

	kfree(scan_cfg_out);
	kfree(scan_chan_list);
done:
	if (ret) {
		spin_lock_irqsave(&adapter->mwifiex_cmd_lock, flags);
		adapter->scan_processing = false;
		spin_unlock_irqrestore(&adapter->mwifiex_cmd_lock, flags);
	}
	return ret;
}
