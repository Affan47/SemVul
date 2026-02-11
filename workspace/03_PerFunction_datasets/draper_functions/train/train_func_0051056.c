mwifiex_send_cmd(struct mwifiex_private *priv, u16 cmd_no,
		     u16 cmd_action, u32 cmd_oid, void *data_buf, bool sync)
{
	int ret;
	struct mwifiex_adapter *adapter = priv->adapter;
	struct cmd_ctrl_node *cmd_node;
	struct host_cmd_ds_command *cmd_ptr;

	if (!adapter) {
		pr_err("PREP_CMD: adapter is NULL\n");
		return -1;
	}

	if (adapter->is_suspended) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: device in suspended state\n");
		return -1;
	}

	if (adapter->hs_enabling && cmd_no != HostCmd_CMD_802_11_HS_CFG_ENH) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: host entering sleep state\n");
		return -1;
	}

	if (adapter->surprise_removed) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: card is removed\n");
		return -1;
	}

	if (adapter->is_cmd_timedout) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: FW is in bad state\n");
		return -1;
	}

	if (adapter->hw_status == MWIFIEX_HW_STATUS_RESET) {
		if (cmd_no != HostCmd_CMD_FUNC_INIT) {
			mwifiex_dbg(adapter, ERROR,
				    "PREP_CMD: FW in reset state\n");
			return -1;
		}
	}


	cmd_node = mwifiex_get_cmd_node(adapter);

	if (!cmd_node) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: no free cmd node\n");
		return -1;
	}


	mwifiex_init_cmd_node(priv, cmd_node, cmd_oid, data_buf, sync);

	if (!cmd_node->cmd_skb) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: no free cmd buf\n");
		return -1;
	}

	memset(skb_put(cmd_node->cmd_skb, sizeof(struct host_cmd_ds_command)),
	       0, sizeof(struct host_cmd_ds_command));

	cmd_ptr = (struct host_cmd_ds_command *) (cmd_node->cmd_skb->data);
	cmd_ptr->command = cpu_to_le16(cmd_no);
	cmd_ptr->result = 0;


	if (cmd_no) {
		switch (cmd_no) {
		case HostCmd_CMD_UAP_SYS_CONFIG:
		case HostCmd_CMD_UAP_BSS_START:
		case HostCmd_CMD_UAP_BSS_STOP:
		case HostCmd_CMD_UAP_STA_DEAUTH:
		case HOST_CMD_APCMD_SYS_RESET:
		case HOST_CMD_APCMD_STA_LIST:
			ret = mwifiex_uap_prepare_cmd(priv, cmd_no, cmd_action,
						      cmd_oid, data_buf,
						      cmd_ptr);
			break;
		default:
			ret = mwifiex_sta_prepare_cmd(priv, cmd_no, cmd_action,
						      cmd_oid, data_buf,
						      cmd_ptr);
			break;
		}
	} else {
		ret = mwifiex_cmd_host_cmd(priv, cmd_ptr, data_buf);
		cmd_node->cmd_flag |= CMD_F_HOSTCMD;
	}


	if (ret) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: cmd %#x preparation failed\n",
			cmd_no);
		mwifiex_insert_cmd_to_free_q(adapter, cmd_node);
		return -1;
	}


	if (cmd_no == HostCmd_CMD_802_11_SCAN ||
	    cmd_no == HostCmd_CMD_802_11_SCAN_EXT) {
		mwifiex_queue_scan_cmd(priv, cmd_node);
	} else {
		mwifiex_insert_cmd_to_pending_q(adapter, cmd_node, true);
		queue_work(adapter->workqueue, &adapter->main_work);
		if (cmd_node->wait_q_enabled)
			ret = mwifiex_wait_queue_complete(adapter, cmd_node);
	}

	return ret;
}
