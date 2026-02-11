mwl8k_post_pervif_cmd(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 struct mwl8k_cmd_pkt *cmd)
{
	if (vif != NULL)
		cmd->macid = MWL8K_VIF(vif)->macid;
	return mwl8k_post_cmd(hw, cmd);
}
