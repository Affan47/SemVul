mwl8k_destroy_ba(struct ieee80211_hw *hw,
			     u8 idx)
{
	struct mwl8k_cmd_bastream *cmd;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_BASTREAM);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le32(MWL8K_BA_DESTROY);

	cmd->destroy_params.ba_context = cpu_to_le32(idx);
	mwl8k_post_cmd(hw, &cmd->header);

	wiphy_debug(hw->wiphy, "Deleted BA stream index %d\n", idx);

	kfree(cmd);
}
