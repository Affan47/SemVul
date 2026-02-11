iwl_mvm_power_configure_uapsd(struct iwl_mvm *mvm,
					  struct ieee80211_vif *vif,
					  struct iwl_mac_power_cmd *cmd)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	enum ieee80211_ac_numbers ac;
	bool tid_found = false;

	for (ac = IEEE80211_AC_VO; ac <= IEEE80211_AC_BK; ac++) {
		if (!mvmvif->queue_params[ac].uapsd)
			continue;

		if (mvm->cur_ucode != IWL_UCODE_WOWLAN)
			cmd->flags |=
				cpu_to_le16(POWER_FLAGS_ADVANCE_PM_ENA_MSK);

		cmd->uapsd_ac_flags |= BIT(ac);


		if (!tid_found && !mvmvif->queue_params[ac].acm) {
			tid_found = true;
			switch (ac) {
			case IEEE80211_AC_VO:
				cmd->qndp_tid = 6;
				break;
			case IEEE80211_AC_VI:
				cmd->qndp_tid = 5;
				break;
			case IEEE80211_AC_BE:
				cmd->qndp_tid = 0;
				break;
			case IEEE80211_AC_BK:
				cmd->qndp_tid = 1;
				break;
			}
		}
	}

	if (!(cmd->flags & cpu_to_le16(POWER_FLAGS_ADVANCE_PM_ENA_MSK))) {
#ifdef CONFIG_IWLWIFI_DEBUGFS

		if (mvmvif->dbgfs_pm.use_ps_poll)
			cmd->flags |=
				cpu_to_le16(POWER_FLAGS_ADVANCE_PM_ENA_MSK);
#endif
		return;
	}

	cmd->flags |= cpu_to_le16(POWER_FLAGS_UAPSD_MISBEHAVING_ENA_MSK);

	if (cmd->uapsd_ac_flags == (BIT(IEEE80211_AC_VO) |
				    BIT(IEEE80211_AC_VI) |
				    BIT(IEEE80211_AC_BE) |
				    BIT(IEEE80211_AC_BK))) {
		cmd->flags |= cpu_to_le16(POWER_FLAGS_SNOOZE_ENA_MSK);
		cmd->snooze_interval = cpu_to_le16(IWL_MVM_PS_SNOOZE_INTERVAL);
		cmd->snooze_window = (mvm->cur_ucode == IWL_UCODE_WOWLAN) ?
			cpu_to_le16(IWL_MVM_WOWLAN_PS_SNOOZE_WINDOW) :
			cpu_to_le16(IWL_MVM_PS_SNOOZE_WINDOW);
	}

	cmd->uapsd_max_sp = IWL_UAPSD_MAX_SP;

	if (mvm->cur_ucode == IWL_UCODE_WOWLAN || cmd->flags &
	    cpu_to_le16(POWER_FLAGS_SNOOZE_ENA_MSK)) {
		cmd->rx_data_timeout_uapsd =
			cpu_to_le32(IWL_MVM_WOWLAN_PS_RX_DATA_TIMEOUT);
		cmd->tx_data_timeout_uapsd =
			cpu_to_le32(IWL_MVM_WOWLAN_PS_TX_DATA_TIMEOUT);
	} else {
		cmd->rx_data_timeout_uapsd =
			cpu_to_le32(IWL_MVM_UAPSD_RX_DATA_TIMEOUT);
		cmd->tx_data_timeout_uapsd =
			cpu_to_le32(IWL_MVM_UAPSD_TX_DATA_TIMEOUT);
	}

	if (cmd->flags & cpu_to_le16(POWER_FLAGS_SNOOZE_ENA_MSK)) {
		cmd->heavy_tx_thld_packets =
			IWL_MVM_PS_SNOOZE_HEAVY_TX_THLD_PACKETS;
		cmd->heavy_rx_thld_packets =
			IWL_MVM_PS_SNOOZE_HEAVY_RX_THLD_PACKETS;
	} else {
		cmd->heavy_tx_thld_packets =
			IWL_MVM_PS_HEAVY_TX_THLD_PACKETS;
		cmd->heavy_rx_thld_packets =
			IWL_MVM_PS_HEAVY_RX_THLD_PACKETS;
	}
	cmd->heavy_tx_thld_percentage =
		IWL_MVM_PS_HEAVY_TX_THLD_PERCENT;
	cmd->heavy_rx_thld_percentage =
		IWL_MVM_PS_HEAVY_RX_THLD_PERCENT;
}
