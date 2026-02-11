mwifiex_cmd_mef_cfg(struct mwifiex_private *priv,
		    struct host_cmd_ds_command *cmd,
		    struct mwifiex_ds_mef_cfg *mef)
{
	struct host_cmd_ds_mef_cfg *mef_cfg = &cmd->params.mef_cfg;
	struct mwifiex_fw_mef_entry *mef_entry = NULL;
	u8 *pos = (u8 *)mef_cfg;
	u16 i;

	cmd->command = cpu_to_le16(HostCmd_CMD_MEF_CFG);

	mef_cfg->criteria = cpu_to_le32(mef->criteria);
	mef_cfg->num_entries = cpu_to_le16(mef->num_entries);
	pos += sizeof(*mef_cfg);

	for (i = 0; i < mef->num_entries; i++) {
		mef_entry = (struct mwifiex_fw_mef_entry *)pos;
		mef_entry->mode = mef->mef_entry[i].mode;
		mef_entry->action = mef->mef_entry[i].action;
		pos += sizeof(*mef_cfg->mef_entry);

		if (mwifiex_cmd_append_rpn_expression(priv,
						      &mef->mef_entry[i], &pos))
			return -1;

		mef_entry->exprsize =
			cpu_to_le16(pos - mef_entry->expr);
	}
	cmd->size = cpu_to_le16((u16) (pos - (u8 *)mef_cfg) + S_DS_GEN);

	return 0;
}
