mwl8k_cmd_get_watchdog_bitmap(struct ieee80211_hw *hw, u8 *bitmap)
{
	struct mwl8k_cmd_get_watchdog_bitmap *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_GET_WATCHDOG_BITMAP);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));

	rc = mwl8k_post_cmd(hw, &cmd->header);
	if (!rc)
		*bitmap = cmd->bitmap;

	kfree(cmd);

	return rc;
}
