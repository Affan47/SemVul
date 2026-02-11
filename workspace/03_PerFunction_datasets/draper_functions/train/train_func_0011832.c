lbs_submit_command(struct lbs_private *priv,
			       struct cmd_ctrl_node *cmdnode)
{
	unsigned long flags;
	struct cmd_header *cmd;
	uint16_t cmdsize;
	uint16_t command;
	int timeo = 3 * HZ;
	int ret;

	lbs_deb_enter(LBS_DEB_HOST);

	cmd = cmdnode->cmdbuf;

	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->seqnum++;
	cmd->seqnum = cpu_to_le16(priv->seqnum);
	priv->cur_cmd = cmdnode;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	cmdsize = le16_to_cpu(cmd->size);
	command = le16_to_cpu(cmd->command);


	if (command == CMD_802_11_SCAN || command == CMD_802_11_ASSOCIATE)
		timeo = 5 * HZ;

	lbs_deb_cmd("DNLD_CMD: command 0x%04x, seq %d, size %d\n",
		     command, le16_to_cpu(cmd->seqnum), cmdsize);
	lbs_deb_hex(LBS_DEB_CMD, "DNLD_CMD", (void *) cmdnode->cmdbuf, cmdsize);

	ret = priv->hw_host_to_card(priv, MVMS_CMD, (u8 *) cmd, cmdsize);

	if (ret) {
		netdev_info(priv->dev, "DNLD_CMD: hw_host_to_card failed: %d\n",
			    ret);

		priv->dnld_sent = DNLD_RES_RECEIVED;
		lbs_complete_command(priv, cmdnode, ret);
	}

	if (command == CMD_802_11_DEEP_SLEEP) {
		if (priv->is_auto_deep_sleep_enabled) {
			priv->wakeup_dev_required = 1;
			priv->dnld_sent = 0;
		}
		priv->is_deep_sleep = 1;
		lbs_complete_command(priv, cmdnode, 0);
	} else {

		mod_timer(&priv->command_timer, jiffies + timeo);
	}

	lbs_deb_leave(LBS_DEB_HOST);
}
