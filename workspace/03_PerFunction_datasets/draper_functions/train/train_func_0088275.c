iwl_mvm_phy_ctxt_cmd_data(struct iwl_mvm *mvm,
				      struct iwl_phy_context_cmd *cmd,
				      struct cfg80211_chan_def *chandef,
				      u8 chains_static, u8 chains_dynamic)
{
	u8 active_cnt, idle_cnt;


	cmd->ci.band = (chandef->chan->band == IEEE80211_BAND_2GHZ ?
	      PHY_BAND_24 : PHY_BAND_5);

	cmd->ci.channel = chandef->chan->hw_value;
	cmd->ci.width = iwl_mvm_get_channel_width(chandef);
	cmd->ci.ctrl_pos = iwl_mvm_get_ctrl_pos(chandef);


	idle_cnt = chains_static;
	active_cnt = chains_dynamic;


	if (active_cnt == 1 && iwl_mvm_rx_diversity_allowed(mvm)) {
		idle_cnt = 2;
		active_cnt = 2;
	}

	cmd->rxchain_info = cpu_to_le32(iwl_mvm_get_valid_rx_ant(mvm) <<
					PHY_RX_CHAIN_VALID_POS);
	cmd->rxchain_info |= cpu_to_le32(idle_cnt << PHY_RX_CHAIN_CNT_POS);
	cmd->rxchain_info |= cpu_to_le32(active_cnt <<
					 PHY_RX_CHAIN_MIMO_CNT_POS);
#ifdef CONFIG_IWLWIFI_DEBUGFS
	if (unlikely(mvm->dbgfs_rx_phyinfo))
		cmd->rxchain_info = cpu_to_le32(mvm->dbgfs_rx_phyinfo);
#endif

	cmd->txchain_info = cpu_to_le32(iwl_mvm_get_valid_tx_ant(mvm));
}
