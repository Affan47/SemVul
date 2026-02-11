mwl8k_cmd_update_stadb_del(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif, u8 *addr)
{
	struct mwl8k_cmd_update_stadb *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_UPDATE_STADB);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le32(MWL8K_STA_DB_DEL_ENTRY);
	memcpy(cmd->peer_addr, addr, ETH_ALEN);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kfree(cmd);

	return rc;
}
