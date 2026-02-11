iwl_pcie_send_hcmd_sync(struct iwl_trans *trans,
				   struct iwl_host_cmd *cmd)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int cmd_idx;
	int ret;

	IWL_DEBUG_INFO(trans, "Attempting to send sync command %s\n",
		       get_cmd_string(trans_pcie, cmd->id));

	if (WARN(test_and_set_bit(STATUS_SYNC_HCMD_ACTIVE,
				  &trans->status),
		 "Command %s: a command is already active!\n",
		 get_cmd_string(trans_pcie, cmd->id)))
		return -EIO;

	IWL_DEBUG_INFO(trans, "Setting HCMD_ACTIVE for command %s\n",
		       get_cmd_string(trans_pcie, cmd->id));

	cmd_idx = iwl_pcie_enqueue_hcmd(trans, cmd);
	if (cmd_idx < 0) {
		ret = cmd_idx;
		clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
		IWL_ERR(trans,
			"Error sending %s: enqueue_hcmd failed: %d\n",
			get_cmd_string(trans_pcie, cmd->id), ret);
		return ret;
	}

	ret = wait_event_timeout(trans_pcie->wait_command_queue,
				 !test_bit(STATUS_SYNC_HCMD_ACTIVE,
					   &trans->status),
				 HOST_COMPLETE_TIMEOUT);
	if (!ret) {
		struct iwl_txq *txq = &trans_pcie->txq[trans_pcie->cmd_queue];
		struct iwl_queue *q = &txq->q;

		IWL_ERR(trans, "Error sending %s: time out after %dms.\n",
			get_cmd_string(trans_pcie, cmd->id),
			jiffies_to_msecs(HOST_COMPLETE_TIMEOUT));

		IWL_ERR(trans, "Current CMD queue read_ptr %d write_ptr %d\n",
			q->read_ptr, q->write_ptr);

		clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
		IWL_DEBUG_INFO(trans, "Clearing HCMD_ACTIVE for command %s\n",
			       get_cmd_string(trans_pcie, cmd->id));
		ret = -ETIMEDOUT;

		iwl_force_nmi(trans);
		iwl_trans_fw_error(trans);

		goto cancel;
	}

	if (test_bit(STATUS_FW_ERROR, &trans->status)) {
		IWL_ERR(trans, "FW error in SYNC CMD %s\n",
			get_cmd_string(trans_pcie, cmd->id));
		dump_stack();
		ret = -EIO;
		goto cancel;
	}

	if (!(cmd->flags & CMD_SEND_IN_RFKILL) &&
	    test_bit(STATUS_RFKILL, &trans->status)) {
		IWL_DEBUG_RF_KILL(trans, "RFKILL in SYNC CMD... no rsp\n");
		ret = -ERFKILL;
		goto cancel;
	}

	if ((cmd->flags & CMD_WANT_SKB) && !cmd->resp_pkt) {
		IWL_ERR(trans, "Error: Response NULL in '%s'\n",
			get_cmd_string(trans_pcie, cmd->id));
		ret = -EIO;
		goto cancel;
	}

	return 0;

cancel:
	if (cmd->flags & CMD_WANT_SKB) {


		trans_pcie->txq[trans_pcie->cmd_queue].
			entries[cmd_idx].meta.flags &= ~CMD_WANT_SKB;
	}

	if (cmd->resp_pkt) {
		iwl_free_resp(cmd);
		cmd->resp_pkt = NULL;
	}

	return ret;
}
